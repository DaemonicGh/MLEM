
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <strings.h>

#include "mlem.h"
#include "mlem_static.h"


static inline void
error(mlem_errors type)
{
	fprintf(stderr, "MLEM: %s\n", error_messages[type]);
}

static void
print_token(mlem_token_type token)
{
	size_t	i = (token != 0);

	for (; token > 1; i++)
		token >>= 1;
	printf("%s", token_repr[i]);
}

// Dynamic Array/Object Methods

static mlem_structure
DS_new(size_t ele_size)
{
	mlem_structure	ds	= {0};

	ds.data	= malloc((DS_BASE_CAPACITY + 1) * ele_size);
	if (!ds.data)
	{
		error(ERR_MEMORY);
		return (ds);
	}
	bzero(ds.data, ele_size);
	ds.len		= 0;
	ds.capacity	= DS_BASE_CAPACITY;
	ds.span		= ele_size;
	return (ds);
}

static inline mlem_array
DA_new(void)
{
	return (DS_new(sizeof(mlem_value)).array);
}

static inline mlem_object
DO_new(void)
{
	return (DS_new(sizeof(mlem_pair)).object);
}

static bool
DS_grow(mlem_structure *ds)
{
	const size_t	new_capacity = ds->capacity * DS_GROW_RATIO;
	void*			tmp;

	tmp = reallocarray(ds->data, new_capacity + 1, ds->span);
	if (!tmp)
	{
		error(ERR_MEMORY);
		return (false);
	}

	ds->data 		= tmp;
	ds->capacity	= new_capacity;
	return (true);
}

static bool
DA_append(mlem_array *array, mlem_value ele)
{
	mlem_structure	*structure	= (mlem_structure *)array;

	if (array->len == array->capacity && !DS_grow(structure))
		return (false);

	array->data[array->len++]				= ele;
	array->data[array->len]					= MLEM_NULL_VALUE;
	return (true);
}

static bool
DO_append(mlem_object *object, mlem_pair ele)
{
	mlem_structure	*structure = (mlem_structure *)object;

	if (object->len == object->capacity && !DS_grow(structure))
		return (false);

	object->data[object->len++]				= ele;
	object->data[object->len]				= MLEM_NULL_PAIR;
	return (true);
}

static void
DS_destroy(mlem_structure *ds)
{
	free(ds->data);
	*ds = (mlem_structure){0};
}

// Utils

static size_t
streq(const char* s1, const char* s2)
{
	size_t	i;

	for (i = 0; s1[i] && s1[i] == s2[i]; i++);
	if (s2[i])
		return (0);
	return (i);
}

static size_t
streq_list(const char* s, const char** sa)
{
	size_t	i;

	for (i = 0; sa[i]; i++)
	{
		if (streq(s, sa[i]))
			return (i);
	}
	return (ST_N1);
}

static const char*
strchr_bs(const char *s, char c)
{
	for (; *s && *s != c; s++)
	{
		if (*s == '\\')
			s++;
	}
	if (*s == c)
		return (s);
	return (NULL);
}

static const char*
strstr_bs(const char *s1, const char *s2)
{
	for (; (s1 = strchr_bs(s1, *s2)); s1++)
	{
	    if (streq(s1, s2))
			return (s1);
	}
	return (0);
}

static inline mlem_context
context_at_token(mlem_context *mlem, mlem_token *token)
{
	return ((mlem_context){
		.content = token->val, .settings = mlem->settings,
		.line = token->line, .column = token->column, .depth = token->depth
	});
}

//

static bool
move_forward(mlem_context *mlem, size_t amount)
{
	while (amount-- && *mlem->content)
	{
		if (*mlem->content == '\n')
		{
			mlem->line++;
			mlem->column = 0;
		}
		mlem->content++;
		mlem->column++;
	}
	return (*mlem->content);
}

static bool
move_past_blank(mlem_context *mlem)
{
	size_t		match_i;

	while ((match_i = streq_list(mlem->content, skip_triggers)) != ST_N1)
		move_forward(mlem, strlen(skip_triggers[match_i]));
	return (*mlem->content);
}

static void
move_past_statement(mlem_context *mlem, mlem_token *token)
{
	size_t 			i = 1;

	if (token->type == TK_WORD)
	{
		while (streq_list((mlem->content) + i, token_triggers) == ST_N1
			&& !isspace((mlem->content)[i]))
			i++;
		move_forward(mlem, i);
		return ;
	}

	const size_t	len = strlen(token->trigger);

	for (i = 0; token_triggers[i]; i++)
	{
		if (token_triggers[i] != token->trigger)
			continue ;
		if (!token_trigger_ends[i])
			break ;
		move_forward(mlem, strstr_bs(mlem->content + len, token_trigger_ends[i])
			+ strlen(token_trigger_ends[i]) - mlem->content);
		return ;
	}
	move_forward(mlem, len);
}

static mlem_token
get_next_token(mlem_context *mlem)
{
	mlem_token	token;
	size_t		match_i;

	do
	{
		move_past_blank(mlem);

		token = (mlem_token){
			.line = mlem->line, .column = mlem->column, .depth = mlem->depth,
			.val = mlem->content, .type = TK_NULL
		};
		if (!(*token.val))
			break ;

		match_i = streq_list(mlem->content, token_triggers);
		token.trigger = token_triggers[match_i];
		if (match_i != ST_N1)
			token.type = token_trigger_values[match_i];
		else
			token.type = TK_WORD;

		move_past_statement(mlem, &token);
		token.len = mlem->content - token.val;

	}	while (token.type & ~TKG_SIGNIFICANT);
	return (token);
}

static mlem_value
parse_array(mlem_context *mlem, mlem_token *trigger_token)
{
	mlem_array	array = DA_new();
	mlem_token	token;

	if (!array.data)
		return (MLEM_NULL_VALUE);
	do
	{
		printf("Token is : ");
		token = get_next_token(mlem);
		print_token(token.type);
		printf(" at %p\n", token.val);
		if (!token.type)
			break ;
		if (token.type & TK_WORD)
			DA_append(&array, (mlem_value){.type = TYPE_STRING, ._string = strndup(token.val, token.len)});
		else if (token.type & TKG_OPEN)
			DA_append(&array, parse_structure(mlem, &token));
	}	while (token.type & ~TKG_CLOSE);
	if (token.type && trigger_token->type & ~(token.type >> 1))
	{
		error(ERR_WRONG_STRUCTURE_CLOSE);
		return (MLEM_NULL_VALUE);
	}
	return ((mlem_value){.type = TYPE_ARRAY, ._array = array.data});
}

static mlem_token_type
get_structure_type(mlem_context *mlem)
{
	mlem_context	mlem_sp	= *mlem;
	mlem_token		token;

	token = get_next_token(&mlem_sp);
	if (token.type & (TKG_CLOSE | TKG_OPEN))
		return (TK_OPEN_ARRAY);
	if (token.type & ~TK_WORD)
	{
		error(ERR_UNEXPECTED_TOKEN);
		return (TK_NULL);
	}

	token = get_next_token(&mlem_sp);
	if (!token.type)
	{
		error(ERR_UNCLOSED_STRUCTURE);
		return (TK_NULL);
	}
	if (token.type & TK_ASSIGN)
		return (TK_OPEN_OBJECT);
	return (TK_OPEN_ARRAY);
}

static mlem_value
parse_structure(mlem_context *mlem, mlem_token *trigger_token)
{
	mlem_token_type	trigger_type	= trigger_token->type;
	mlem_value		structure		= MLEM_NULL_VALUE;

	if (trigger_token->type & TK_OPEN_UNKNOWN)
		trigger_type = get_structure_type(mlem);

	if (trigger_type & TK_OPEN_ARRAY)
		structure = parse_array(mlem, trigger_token);
	//else if (trigger_type & TK_OPEN_OBJECT)
	//	structure = parse_object(mlem, trigger_token);
	else
		error(ERR_UNEXPECTED_ERROR);
	return (structure);
}

static void
parse_start(mlem_context *mlem)
{
	(void)mlem;
	return ;
}

static mlem_context
init_context(char* content, mlem_parser_settings settings)
{
	mlem_context	mlem = {
		.line = 1, .column = 1, .depth = 0,
		.content = content, .settings = settings
	};
	return (mlem);
}

mlem_value
mlem_parse(char* content, mlem_parser_settings settings)
{
	mlem_token			start_token = {.type = TK_OPEN_UNKNOWN, .trigger = token_triggers[6]};
	mlem_context		mlem;
	mlem_value			structure;

	mlem = init_context(content, settings);
	if (!mlem.content)
		return (MLEM_NULL_VALUE);
	parse_start(&mlem);
	printf("Starting parsing\n");
	structure = parse_structure(&mlem, &start_token);
	return (structure);
}

static char*
open_and_read_file(const char *filename)
{
	FILE	*file;
	char	*content;
	size_t	content_size;

	file = fopen(filename, "r");
	if (!file)
	{
		error(ERR_FILE);
		return (NULL);
	}

	fseek(file, 0, SEEK_END);
	content_size = ftell(file);
	fseek(file, 0, SEEK_SET);

	content = malloc(content_size + 1);
	if (!content)
	{
		error(ERR_MEMORY);
		return (NULL);
	}

	fread(content, 1, content_size, file);
	content[content_size] = '\0';

	fclose(file);
	return (content);
}

mlem_value
mlem_parse_file(const char *filename, mlem_parser_settings settings)
{
	mlem_value	value;
	char*		str;

	str = open_and_read_file(filename);
	if (!str)
		return (MLEM_NULL_VALUE);
	printf("Read File\n");
	value = mlem_parse(str, settings);
	//free(str);
	return (value);
}

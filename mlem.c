
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>

#include "mlem.h"

// Private header

typedef enum {
	ERR_EMPTY,
	ERR_FILE,
	ERR_MEMORY,
}	Errors;

typedef struct
{
	Token*	tokens;
	Token	*last;
	size_t	len;
	size_t	size;
}	TokenArray;

// Globals

static const char*	error_messages[] = {
	"",
	"Unable to open file",
	"Memory error"
};

static const char*	token_triggers[] = {
	"'''", "///", "\"\"\"",
	"//", "/*", "*/",
	"[", "]", "=", "'", "\"",
	"{", "}", ":", NULL
};

static const TokenType	token_trigger_values[] = {
	TK_ML_WORD_DEL, TK_ML_COMMENT_DEL, TK_ML_WORD_DEL,
	TK_COMMENT, TK_ML_COMMENT_START, TK_ML_COMMENT_END,
	TK_OPEN_UNKNOWN, TK_CLOSE_UNKNOWN, TK_ASSIGN, TK_WORD_DEL, TK_ML_WORD_DEL,
	TK_OPEN_OBJECT, TK_CLOSE_OBJECT, TK_ASSIGN, TK_NULL
};

static const char* token_trigger_ends[] ={
	"'''", "///", "\"\"\"",
	"\n", "*/", NULL,
	NULL, NULL, NULL, "'", "\"",
	NULL, NULL, NULL, NULL
};

static const char*	skip_triggers[] = {
	" ", "\t", "\n", ",", NULL
};

static const char*	token_repr[] = {
	"N", "W", "[", "]", "'", "\"", "//", "///", "/*", "*/",
	"K", "V", "=", "(", ")", "{", "}", NULL
};

// Utils

static inline void	error(Errors type)
{
	fprintf(stderr, "MLEM: %s\n", error_messages[type]);
}

static size_t	streq(const char* s1, const char* s2)
{
	size_t	i;

	for (i = 0; s1[i] && s1[i] == s2[i]; i++);
	if (s2[i])
		return (0);
	return (i);
}

static size_t	streq_list(const char* s, const char** sa)
{
	size_t	i;

	for (i = 0; sa[i]; i++)
	{
		if (streq(s, sa[i]))
			return (i);
	}
	return (-1);
}

static const char*	strchr_bs(const char *s, char c)
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

static const char*	strstr_bs(const char *s1, const char *s2)
{
	for (; (s1 = strchr_bs(s1, *s2)); s1++)
	{
	    if (streq(s1, s2))
			return (s1);
	}
	return (0);
}

static void	print_token(Token *token)
{
	printf("%s", token_repr[token->type]);
}

//

static bool	move_forward(const char* *content, size_t *line, size_t *column, size_t amount)
{
	while (amount-- && **content)
	{
		if (**content == '\n')
		{
			(*line)++;
			*column = 0;
		}
		(*content)++;
		(*column)++;
	}
	return (**content);
}

static void	move_past_blank(const char* *content, size_t *line, size_t *column)
{
	size_t		match_i;

	while ((match_i = streq_list(*content, skip_triggers)) != (size_t)-1)
		move_forward(content, line, column, strlen(skip_triggers[match_i]));
}

static void	move_past_statement(Token *token, const char* *content, size_t *line, size_t *column)
{
	size_t 			i = 1;

	if (token->type == TK_WORD)
	{
		while (streq_list((*content) + i, token_triggers) == (size_t)-1
			&& !isspace((*content)[i]))
			i++;
		move_forward(content, line, column, i);
		return ;
	}

	const size_t	len = strlen(token->trigger);

	for (i = 0; token_triggers[i]; i++)
	{
		if (!token_trigger_ends[i] || token_triggers[i] != token->trigger)
			continue ;
		move_forward(content, line, column,
			strstr_bs(*content + len, token_trigger_ends[i])
			+ strlen(token_trigger_ends[i]) - *content);
		return ;
	}
	move_forward(content, line, column, len);
}

static Token	mlem_get_next_token(const char* *content, size_t *line, size_t *column)
{
	size_t		match_i;
	Token		token = (Token){
		.line = *line,
		.column = *column,
		.val = *content
	};

	match_i = streq_list(*content, token_triggers);
	token.trigger = token_triggers[match_i];
	if (match_i != (size_t)-1)
	{
		token.type = token_trigger_values[match_i];
		return (token);
	}
	token.type = TK_WORD;
	return (token);
}

Token*	mlem_tokenize(const char* content)
{
	Token	token;
	size_t	line	= 1;
	size_t	column	= 1;

	while (*content)
	{
		move_past_blank(&content, &line, &column);
		if (!*content)
			break ;
		token = mlem_get_next_token(&content, &line, &column);
		print_token(&token);
		printf(": %.*s\n", (int)strcspn(token.val, "\n=[]"), token.val);
		if (token.type == TK_NULL)
			break ;
		move_past_statement(&token, &content, &line, &column);
	}
	return (NULL);
}

mlem_value	mlem_parse(const char* content)
{
	(void)content;
	return (MLEM_NULL_VALUE);
}

char*	open_and_read_file(const char *filename)
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

mlem_value	mlem_parse_file(const char *filename)
{
	char*	str;

	str = open_and_read_file(filename);
	if (!str)
		return (MLEM_NULL_VALUE);
	return (mlem_parse(str));
}

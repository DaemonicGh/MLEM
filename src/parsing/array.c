
#include <stdlib.h>
#include <string.h>

#include "mlem.h"
#include "parser.h"
#include "structures.h"
#include "errors.h"
#include "tokens.h"

static bool
append_value(mlem_context *mlem, mlem_array *array, mlem_token *token)
{
	mlem_value	val;

	do {
		if (token->type & TK_WORD)
		{
			val = (mlem_value){
				.type = TYPE_STRING,
				.val_string = strndup(token->val, token->len)
			};
			if (!val.val_string || !DA_append(array, val))
			{
				free(val.val_string);
				break ;
			}
		}
		else if (token->type & TKG_OPEN)
		{
			val = parse_structure(mlem, token);
			if (!val.type)
				return (false);
			if (!DA_append(array, val))
				break ;
		}
		return (true);
	} while(false);
	error(mlem, ERR_MEMORY);
	return (false);
}

static mlem_value
send_array(mlem_array *array)
{
	if (array->len + DS_CROP_THRESHOLD < array->capacity)
		DS_resize((mlem_structure *)array, array->len);
	return ((mlem_value){.type = TYPE_ARRAY, .val_array = array->data});
}

mlem_value
parse_array(mlem_context *mlem, mlem_token *trigger_token)
{
	mlem_array	array = DA_new();
	mlem_token	token = MLEM_NULL_TOKEN;

	if (!array.data)
		return (MLEM_NULL_VALUE);
	while (!(token.type & TKG_CLOSE))
	{
		token = get_next_token(mlem);
		if (mlem->depth == 0 && !*mlem->content)
			return (send_array(&array));
		if (!token.type || !append_value(mlem, &array, &token))
		{
			DA_destroy(&array, true);
			return (MLEM_NULL_VALUE);
		}
	}
	if (mlem->depth == 0)
		error(mlem, ERR_UNEXPECTED_TOKEN);
	else if (trigger_token->type & ~(token.type >> 1))
		error(mlem, ERR_WRONG_STRUCTURE_CLOSE);
	else
		return (send_array(&array));
	DA_destroy(&array, true);
	return (MLEM_NULL_VALUE);
}


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

	if (token->type & TKG_WORD)
	{
		val = (mlem_value){
			.type = MLEM_TYPE_STRING,
			.val_string = strndup(token->val, token->len)
		};
		if (val.val_string && DA_append(array, val))
			return (true);
		free(val.val_string);
		mlem->error = set_error(ERR_MEMORY);
	}
	else if (token->type & TKG_OPEN)
	{
		val = parse_structure(mlem, token);
		if (!val.type)
			return (false);
		if (DA_append(array, val))
			return (true);
		mlem->error = set_error(ERR_MEMORY);
	}
	else
		set_error_t(mlem, token, ERR_UNEXPECTED_TOKEN);
	return (false);
}

static mlem_value
send_array(mlem_array *array)
{
	if (array->len + DS_CROP_THRESHOLD < array->capacity)
		DS_resize((mlem_structure *)array, array->len);
	return ((mlem_value){.type = MLEM_TYPE_ARRAY, .val_array = array->data});
}

mlem_value
parse_array(mlem_context *mlem, mlem_token *trigger_token)
{
	mlem_array	array = DA_new();
	mlem_token	token = MLEM_NULL_TOKEN;

	if (!array.data)
	{
		mlem->error = set_error(ERR_MEMORY);
		return (MLEM_ERROR_VALUE(ERR_MEMORY));
	}

	while (true)
	{
		token = get_next_token(mlem);
		if (!token.type)
		{
			if (!mlem->error)
				return (send_array(&array));
			break ;
		}
		if (token.type & TKG_CLOSE)
		{
			if (mlem->depth == 0)
				set_error_t(mlem, &token, ERR_UNEXPECTED_TOKEN);
			else if (trigger_token->type & ~(token.type >> 1))
				set_error_t(mlem, &token, ERR_WRONG_STRUCTURE_CLOSE);
			else
				return (send_array(&array));
			break ;
		}
		if (!append_value(mlem, &array, &token))
			break ;
	}
	DA_destroy(&array, true);
	return (MLEM_ERROR_VALUE(mlem->error));
}

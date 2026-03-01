
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "context.h"
#include "mlem.h"
#include "parser.h"
#include "structures.h"
#include "errors.h"
#include "tokens.h"

static bool
get_key_value_tokens(mlem_context *mlem, mlem_token *key, mlem_token *value)
{
	mlem_token	assign;

	*key = MLEM_NULL_TOKEN;
	*value = MLEM_NULL_TOKEN;

	*key = get_next_token(mlem);
	if (!key->type && mlem->error)
		return (false);
	if (!key->type && key->type & ~TKG_OBJECT_KEY)
	{
		set_error_t(mlem, key, ERR_UNEXPECTED_TOKEN);
		return (false);
	}
	if (key->type & TKG_CLOSE)
		return (true);

	assign = get_next_token(mlem);
	if (!assign.type && mlem->error)
	 	return (false);
	if (!assign.type || assign.type & ~TK_ASSIGN)
	{
		set_error_t(mlem, &assign, ERR_EXPECTED_ASSIGN);
		return (false);
	}

	*value = get_next_token(mlem);
	if (!value->type && mlem->error)
	{
		set_error_l(mlem, ERR_EXPECTED_VALUE);
		return (false);
	}
	if (!assign.type && key->type & ~TKG_OBJECT_VALUE)
	{
		set_error_t(mlem, value, ERR_UNEXPECTED_TOKEN);
		return (false);
	}
	return (true);
}

static bool
append_pair(mlem_context *mlem, mlem_object *object, mlem_token *key, mlem_token *value)
{
	mlem_pair	val;

	if (key->type & ~TKG_WORD)
	{
		set_error_t(mlem, key, ERR_UNEXPECTED_TOKEN);
		return (false);
	}
	val.key = strndup(key->val, key->len);
	if (!val.key)
	{
		set_error(ERR_MEMORY);
		return (false);
	}

	if (value->type & TKG_WORD)
	{
		val.value = (mlem_value){
			.type = MLEM_TYPE_STRING,
			.val_string = strndup(value->val, value->len)
		};
		if (val.value.val_string && DO_append(object, val))
			return (true);
		free(val.value.val_string);
		set_error_l(mlem, ERR_MEMORY);
	}
	else if (value->type & TKG_OPEN)
	{
		val.value = parse_structure(mlem, value);
		if (val.value.type)
		{
			if (DO_append(object, val))
				return (true);
			mlem->error = set_error(ERR_MEMORY);
		}
	}
	else
		set_error_t(mlem, value, ERR_UNEXPECTED_TOKEN);
	free(val.key);
	return (false);
}

static mlem_value
send_object(mlem_object *object)
{
	if (object->len + DS_CROP_THRESHOLD < object->capacity)
		DS_resize((mlem_structure *)object, object->len);
	return ((mlem_value){.type = MLEM_TYPE_OBJECT, .val_object = object->data});
}

mlem_value
parse_object(mlem_context *mlem, mlem_token *trigger_token)
{
	mlem_object	object	= DO_new();
	mlem_token	key;
	mlem_token	value;

	if (!object.data)
	{
		mlem->error = set_error(ERR_MEMORY);
		return (MLEM_ERROR_VALUE(ERR_MEMORY));
	}

	while (true) {
		if (!get_key_value_tokens(mlem, &key, &value))
		{
			if (!mlem->error)
				return (send_object(&object));
			break ;
		}
		if (key.type & TKG_CLOSE)
		{
			if (mlem->depth == 0)
				set_error_t(mlem, &key, ERR_UNEXPECTED_TOKEN);
			else if (trigger_token->type & ~(key.type >> 1))
				set_error_t(mlem, &key, ERR_WRONG_STRUCTURE_CLOSE);
			else
				return (send_object(&object));
			break ;
		}
		if (!append_pair(mlem, &object, &key, &value))
			break ;
	}
	DO_destroy(&object, true);
	return (MLEM_ERROR_VALUE(mlem->error));
}

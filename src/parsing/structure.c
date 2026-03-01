
#include <stdio.h>

#include "errors.h"
#include "mlem.h"
#include "parser.h"
#include "tokens.h"

mlem_value_type
static get_structure_type(mlem_context *mlem)
{
	mlem_context	mlem_sp	= *mlem;
	mlem_token		token;

	token = get_next_token(&mlem_sp);
	if (!token.type)
		return (MLEM_TYPE_NULL);
	if (token.type & (TKG_CLOSE | TKG_OPEN))
		return (MLEM_TYPE_ARRAY);
	if (token.type & ~TKG_WORD)
	{
		set_error_l(mlem, ERR_UNEXPECTED_TOKEN);
		return (MLEM_TYPE_NULL);
	}

	token = get_next_token(&mlem_sp);
	if (!token.type && mlem->error)
		return (MLEM_TYPE_NULL);
	if (token.type & TK_ASSIGN)
		return (MLEM_TYPE_OBJECT);
	return (MLEM_TYPE_ARRAY);
}

mlem_value
parse_structure(mlem_context *mlem, mlem_token *trigger_token)
{
	mlem_value		structure = MLEM_NULL_VALUE;

	mlem->depth++;
	if (trigger_token->type & TK_OPEN_UNKNOWN)
	{
		printf("(\n");
		structure.type = get_structure_type(mlem);
		printf(")\n");
	}
	if (structure.type == MLEM_TYPE_ARRAY ||
		trigger_token->type & TK_OPEN_ARRAY)
		structure = parse_array(mlem, trigger_token);
	else if (structure.type == MLEM_TYPE_OBJECT ||
		trigger_token->type & TK_OPEN_OBJECT)
		structure = parse_object(mlem, trigger_token);
	else
		structure = MLEM_ERROR_VALUE(mlem->error);

	mlem->depth--;
	return (structure);
}

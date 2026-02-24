
#include "mlem.h"
#include "parser.h"
#include "tokens.h"
#include "errors.h"

mlem_token_type
get_structure_type(mlem_context *mlem)
{
	mlem_context	mlem_sp	= *mlem;
	mlem_token		token;

	token = get_next_token(&mlem_sp);
	if (!token.type)
		return (TK_NULL);
	if (token.type & (TKG_CLOSE | TKG_OPEN))
		return (TK_OPEN_ARRAY);
	if (token.type & ~TK_WORD)
	{
		error(mlem, ERR_UNEXPECTED_TOKEN);
		return (TK_NULL);
	}

	token = get_next_token(&mlem_sp);
	if (!token.type)
		return (TK_NULL);
	if (mlem->depth == 0 && !*mlem_sp.content)
	{
		error(mlem, ERR_UNCLOSED_STRUCTURE);
		return (TK_NULL);
	}
	if (token.type & TK_ASSIGN)
		return (TK_OPEN_OBJECT);
	return (TK_OPEN_ARRAY);
}

mlem_value
parse_structure(mlem_context *mlem, mlem_token *trigger_token)
{
	mlem_token_type	trigger_type	= trigger_token->type;
	mlem_value		structure		= MLEM_NULL_VALUE;

	mlem->depth++;
	if (trigger_token->type & TK_OPEN_UNKNOWN)
		trigger_type = get_structure_type(mlem);

	if (trigger_type & TK_OPEN_ARRAY)
		structure = parse_array(mlem, trigger_token);
	//if (trigger_type & TK_OPEN_OBJECT)
	//	structure = parse_object(mlem, trigger_token);
	else if (trigger_type)
		error(mlem, ERR_UNEXPECTED_ERROR);
	mlem->depth--;
	return (structure);
}

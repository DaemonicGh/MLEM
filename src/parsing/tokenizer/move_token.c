
#include <stdio.h>
#include <string.h>

#include "errors.h"
#include "tokens.h"
#include "utils.h"

static size_t
move_past_symbol(mlem_context *mlem, mlem_token *token)
{
	const char	*end = NULL;
	size_t		i;

	for (i = 0; !end; i++)
	{
		if (!mlem->content[i] || (token->trigger->error &&
			multistreq(mlem->content + i, token->trigger->error)))
		{
			error(mlem, ERR_UNCLOSED_SYMBOL);
			return (ST_N1);
		}
		end = multistreq(mlem->content + i, token->trigger->end);
		i = skip_potential_backslash(mlem->content + i) - mlem->content;
	}
	move_forward(mlem, --i + strlen(end));
	return (mlem->content - token->val);
}

size_t
move_past_token(mlem_context *mlem, mlem_token *token)
{
	if (token->type & TK_WORD)
		move_past_word(mlem);
	else
	{
		move_forward(mlem, strlen(multistreq(token->val, token->trigger->start)));
		if (token->type & TKG_EXTENDS)
			return (move_past_symbol(mlem, token));
	}
	return (mlem->content - token->val);
}

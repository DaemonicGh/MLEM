
#include <stdio.h>
#include <string.h>

#include "errors.h"
#include "tokens.h"
#include "utils.h"

static const char
*move_past_symbol(mlem_context *mlem, mlem_token *token)
{
	const char	*end = NULL;
	size_t		i;

	for (i = 0; !end; i++)
	{
		if (!mlem->content[i] || (token->trigger->error &&
			multistreq(mlem->content + i, token->trigger->error)))
		{
			error(mlem, ERR_UNCLOSED_SYMBOL);
			return (NULL);
		}
		end = multistreq(mlem->content + i, token->trigger->end);
		i = skip_potential_backslash(mlem->content + i) - mlem->content;
	}
	move_forward(mlem, --i);
	return (end);
}

size_t
move_past_token(mlem_context *mlem, mlem_token *token)
{
	const char	*end;
	size_t		len;

	if (token->type & TK_WORD)
	{
		move_past_word(mlem);
		return (mlem->content - token->val);
	}
	len = strlen(multistreq(token->val, token->trigger->start));
	move_forward(mlem, len);
	token->val += len;

	if (token->type & TKG_EXTENDS)
	{
		end = move_past_symbol(mlem, token);
		if (!end)
			return (ST_N1);
		len = mlem->content - token->val;
		move_forward(mlem, strlen(end));
		if (token->type & TKG_WORD_CONTENT)
			token->type = TK_WORD;
		else
			len = mlem->content - token->val;
	}
	return (len);
}

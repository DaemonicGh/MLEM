
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#include "context.h"
#include "errors.h"
#include "tokens.h"

static mlem_token
get_token(mlem_context *mlem)
{
	const char	*trigger_str = "";
	mlem_token	token = {.type = TK_WORD};

	token.trigger = get_start_trigger_p(mlem->content, &trigger_str);
	if (token.trigger)
	{
		token.type = token.trigger->type;
		move_forward(mlem, strlen(trigger_str));
	}
	if (token.trigger && token.type & ~TKG_EXTENDS)
		return (token);

	token.val = mlem->content;
	if (token.trigger)
		move_past_extend(mlem, &token, &trigger_str);
	else
		move_past_word(mlem);
	if (mlem->content == token.val)
		return (MLEM_NULL_TOKEN);
	token.len = mlem->content - strlen(trigger_str) - token.val;
	return (token);
}

mlem_token
get_next_token(mlem_context *mlem)
{
	mlem_token					token;

	while (true)
	{
		move_past_blank(mlem);

		if (!(*mlem->content))
		{
			if (mlem->depth > 0)
				error(NULL, ERR_UNCLOSED_STRUCTURE);
			return (MLEM_NULL_TOKEN);
		}

		token = get_token(mlem);

		printf("Token = ");
		print_token(token.type);
		printf(" %.*s\n", (int)token.len, token.val);

		if (!token.type || token.type & TKG_SIGNIFICANT)
			return (token);
	}
}

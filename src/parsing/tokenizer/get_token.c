
#include <stdbool.h>
#include <stdio.h>

#include "errors.h"
#include "tokens.h"
#include "utils.h"

mlem_token
get_next_token(mlem_context *mlem)
{
	mlem_token					token;

	do
	{
		move_past_blank(mlem);

		token = (mlem_token){.val = mlem->content, .type = TK_NULL};
		if (!(*token.val))
		{
			if (mlem->depth > 0)
				error(NULL, ERR_UNCLOSED_STRUCTURE);
			return (MLEM_NULL_TOKEN);
		}

		token.trigger = get_trigger(mlem->content);
		if (token.trigger)
			token.type = token.trigger->type;
		else
			token.type = TK_WORD;

		token.len = move_past_token(mlem, &token);
		if (token.len == ST_N1)
			return (MLEM_NULL_TOKEN);

		printf("Token = ");
		print_token(token.type);
		printf("\n");

	}	while (token.type & ~TKG_SIGNIFICANT);
	return (token);
}

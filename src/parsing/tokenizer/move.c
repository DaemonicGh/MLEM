
#include <ctype.h>
#include <string.h>
#include <stdio.h>

#include "context.h"
#include "tokens.h"
#include "errors.h"
#include "utils.h"

bool
move_forward(mlem_context *mlem, size_t amount)
{
	while (amount-- && *mlem->content)
	{
		if (*mlem->content == '\n')
		{
			mlem->line++;
			mlem->column = 0;
		}
		mlem->content++;
		mlem->column++;
	}
	return (*mlem->content);
}

bool
move_past_blank(mlem_context *mlem)
{
	size_t		match_i;

	while (*mlem->content)
	{
		match_i = streq_list(mlem->content, skip_triggers);
		if (match_i == ST_N1)
			break ;
		move_forward(mlem, strlen(skip_triggers[match_i]));
	}
	return (*mlem->content);
}

bool
move_past_word(mlem_context *mlem)
{
	size_t 			i = 1;

	while (!get_start_trigger(mlem->content + i) && !isspace(mlem->content[i]))
		i++;
	move_forward(mlem, i);
	return (*mlem->content);
}

void
move_past_extend(mlem_context *mlem, mlem_token *token, const char **trigger_str)
{
	size_t	end = ST_N1;
	size_t	i;

	for (i = 0; end == ST_N1; i++)
	{
		if (!mlem->content[i] || (*token->trigger->error && streq_list(
				mlem->content + i, (const char **)token->trigger->error
			) != ST_N1))
		{
			error(mlem, ERR_UNCLOSED_SYMBOL);
			return ;
		}
		end = streq_list(mlem->content + i, (const char **)token->trigger->end);
		i = skip_potential_backslash(mlem->content + i) - mlem->content;
	}
	*trigger_str = token->trigger->end[end];
	move_forward(mlem, --i + strlen(*trigger_str));
}

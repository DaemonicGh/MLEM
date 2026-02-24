
#include <ctype.h>
#include <string.h>

#include "context.h"
#include "tokens.h"
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

	while ((match_i = streq_list(mlem->content, skip_triggers)) != ST_N1)
		move_forward(mlem, strlen(skip_triggers[match_i]));
	return (*mlem->content);
}

bool
move_past_word(mlem_context *mlem)
{
	size_t 			i = 1;

	while (!get_trigger(mlem->content + i) && !isspace(mlem->content[i]))
		i++;
	move_forward(mlem, i);
	return (*mlem->content);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 13:59:06 by rprieur           #+#    #+#             */
/*   Updated: 2026/04/02 14:00:37 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>

#include "context.h"
#include "mlem.h"
#include "tokens.h"
#include "errors.h"
#include "utils.h"

bool
move_forward(t_mlem_context *mlem, size_t amount)
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
move_past_blank(t_mlem_context *mlem)
{
	size_t		match_i;

	while (*mlem->content)
	{
		match_i = streq_list(mlem->content, g_skip_triggers);
		if (match_i == ST_N1)
			break ;
		move_forward(mlem, strlen(g_skip_triggers[match_i]));
	}
	return (*mlem->content);
}

bool
move_past_word(t_mlem_context *mlem)
{
	size_t 			i = 1;

	while (*(mlem->content + i) &&
		!get_start_trigger(mlem->content + i) &&
		streq_list(mlem->content + i, g_skip_triggers) == ST_N1)
		i++;
	move_forward(mlem, i);
	return (*mlem->content);
}

bool
move_past_extend(t_mlem_context *mlem, t_mlem_token *token, const char **trigger_str)
{
	size_t	end = ST_N1;
	size_t	i;

	for (i = 0; end == ST_N1; i++)
	{
		if (!mlem->content[i] || (*token->trigger->error && streq_list(
				mlem->content + i, (const char **)token->trigger->error
			) != ST_N1))
		{
			set_error_t(mlem, token, ERR_UNCLOSED_SYMBOL);
			return (false);
		}
		end = streq_list(mlem->content + i, (const char **)token->trigger->end);
		i = skip_potential_backslash(mlem->content + i) - mlem->content;
	}
	*trigger_str = token->trigger->end[end];
	move_forward(mlem, --i + strlen(*trigger_str));
	return (true);
}

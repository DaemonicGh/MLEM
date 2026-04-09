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
		if (match_i == (size_t) - 1)
			break ;
		move_forward(mlem, mlem_strlen(g_skip_triggers[match_i]));
	}
	return (*mlem->content);
}

bool
	move_past_word(t_mlem_context *mlem)
{
	size_t	i;

	i = 1;
	while (*(mlem->content + i)
		&& !get_start_trigger(mlem->content + i)
		&& streq_list(mlem->content + i, g_skip_triggers) == (size_t) -1)
		i++;
	move_forward(mlem, i);
	return (*mlem->content);
}

bool
	move_past_extend(
		t_mlem_context *mlem, t_mlem_token *token, const char **trigger_str)
{
	size_t	end;
	size_t	i;

	end = -1;
	i = 0;
	while (end == (size_t) -1)
	{
		if (!mlem->content[i] || (*token->trigger->error && streq_list(
					mlem->content + i, (const char **)token->trigger->error
				) != (size_t) - 1))
		{
			set_error_t(mlem, token, ERR_UNCLOSED_SYMBOL);
			return (false);
		}
		end = streq_list(mlem->content + i, (const char **)token->trigger->end);
		i = skip_potential_backslash(mlem->content + i) - mlem->content + 1;
	}
	*trigger_str = token->trigger->end[end];
	move_forward(mlem, --i + mlem_strlen(*trigger_str));
	return (true);
}

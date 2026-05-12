/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trigger.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 03:03:01 by rprieur           #+#    #+#             */
/*   Updated: 2026/05/08 00:17:26 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "parser.h"

void
	move_forward(t_mlem_parser *mlem, size_t amount)
{
	while (amount-- && *mlem->pos.content)
	{
		if (*mlem->pos.content == '\n')
		{
			mlem->pos.line++;
			mlem->pos.column = 0;
		}
		mlem->pos.content++;
		mlem->pos.column++;
	}
}

t_mlem_token_trigger
	*get_trigger_str(const char *str)
{
	const uint8_t			*triggers;
	t_mlem_token_trigger	*trigger;
	size_t					i;

	if (*str < 0)
		return (&g_mlem_data.tokens[TRG_CONTINUE]);
	triggers = g_mlem_data.char_data.tokens[(int)*str];
	i = 0;
	trigger = &g_mlem_data.tokens[triggers[i++]];
	while (trigger->value[0] && !strctn(str, trigger->value))
		trigger = &g_mlem_data.tokens[triggers[i++]];
	return (trigger);
}

t_mlem_token_trigger
	*get_trigger(t_mlem_parser *mlem)
{
	return (get_trigger_str(mlem->pos.content));
}

void
	move_past_trigger(t_mlem_parser *mlem, t_mlem_token_trigger *trigger)
{
	if (trigger->len)
		move_forward(mlem, trigger->len);
	else
		move_forward(mlem, 1);
}

bool
	trigger_in_list(t_mlem_token_trigger *trigger, const uint8_t *list)
{
	size_t		i;

	i = 0;
	while (list[i])
	{
		if (trigger == &g_mlem_data.tokens[list[i]])
			return (true);
		i++;
	}
	return (false);
}

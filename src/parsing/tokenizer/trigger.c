/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trigger.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 13:59:06 by rprieur           #+#    #+#             */
/*   Updated: 2026/04/02 14:00:37 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "utils.h"

t_mlem_token_trigger
*get_start_trigger(const char *s)
{
	size_t	i;

	for (i = 0; g_token_triggers[i].type; i++)
	{
		if (streq_list(s, (const char **)g_token_triggers[i].start) != ST_N1)
			return (&g_token_triggers[i]);
	}
	return (NULL);
}

t_mlem_token_trigger
*get_start_trigger_p(const char *s, const char **trigger_str)
{
	size_t	pos;
	size_t	i;

	for (i = 0; g_token_triggers[i].type; i++)
	{
		pos = streq_list(s, (const char **)g_token_triggers[i].start);
		if (pos == ST_N1)
			continue ;
		*trigger_str = g_token_triggers[i].start[pos];
		return (&g_token_triggers[i]);
	}
	return (NULL);
}

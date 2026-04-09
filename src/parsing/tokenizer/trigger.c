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

	i = 0;
	while (g_token_triggers[i].type)
	{
		if (streq_list(s, (const char **)g_token_triggers[i].start)
			!= (size_t) - 1)
			return (&g_token_triggers[i]);
		i++;
	}
	return (NULL);
}

t_mlem_token_trigger
	*get_start_trigger_p(const char *s, const char **trigger_str)
{
	size_t	pos;
	size_t	i;

	i = 0;
	while (g_token_triggers[i].type)
	{
		pos = streq_list(s, (const char **)g_token_triggers[i].start);
		if (pos != (size_t) - 1)
		{
			*trigger_str = g_token_triggers[i].start[pos];
			return (&g_token_triggers[i]);
		}
		i++;
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 13:59:06 by rprieur           #+#    #+#             */
/*   Updated: 2026/04/02 14:00:37 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "errors.h"
#include "utils.h"

static t_mlem_token
	get_token(t_mlem_context *mlem)
{
	const char		*trigger_str = "";
	t_mlem_token	token;

	token.type = TK_WORD;
	token.trigger = get_start_trigger_p(mlem->content, &trigger_str);
	if (token.trigger)
	{
		token.type = token.trigger->type;
		token.val = mlem->content;
		token.len = mlem_strlen(trigger_str);
		move_forward(mlem, token.len);
		if (token.type & ~TKG_EXTENDS)
			return (token);
	}
	token.val = mlem->content;
	if (token.trigger)
		move_past_extend(mlem, &token, &trigger_str);
	else
		move_past_word(mlem);
	if (mlem->content == token.val)
		return ((t_mlem_token){0});
	token.len = mlem->content - mlem_strlen(trigger_str) - token.val;
	return (token);
}

t_mlem_token
	get_next_token(t_mlem_context *mlem)
{
	t_mlem_token	token;

	while (true)
	{
		move_past_blank(mlem);
		if (!(*mlem->content))
		{
			if (mlem->depth > 0)
				set_error_l(mlem, ERR_UNCLOSED_STRUCTURE);
			return ((t_mlem_token){0});
		}
		token = get_token(mlem);
		if (!token.type || token.type & TKG_SIGNIFICANT)
			return (token);
	}
}

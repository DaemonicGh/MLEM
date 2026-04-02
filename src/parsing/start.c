/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 13:59:06 by rprieur           #+#    #+#             */
/*   Updated: 2026/04/02 14:00:37 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlem.h"
#include "parser.h"

void
parse_start(t_mlem_context *mlem)
{
	(void)mlem;
	return ;
}

t_mlem_context
init_context(char *content, t_mlem_settings settings)
{
	t_mlem_context	mlem = {
		.line = 1, .column = 1, .depth = -1,
		.content = content, .settings = settings,
		.error = ERR_NONE
	};
	return (mlem);
}

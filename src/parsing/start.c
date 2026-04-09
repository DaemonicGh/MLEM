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

#include "errors.h"
#include "mlem.h"
#include "parser.h"

void
	parse_start(t_mlem_context *mlem)
{
	(void)mlem;
	return ;
}

t_mlem_context
	init_context(char *content, const t_mlem_value *constants)
{
	t_mlem_context	mlem;

	mlem = (t_mlem_context){
		.line = 1, .column = 1, .depth = -1,
		.content = content, .constants = constants,
		.error = ERR_NONE
	};
	if (constants && constants->type != MLEM_TYPE_NULL
		&& constants->type != MLEM_TYPE_OBJECT)
		mlem.error = set_error(ERR_CONSTANT_TABLE_IS_NOT_OBJECT);
	return (mlem);
}

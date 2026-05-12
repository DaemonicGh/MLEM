/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subtemplate_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 16:59:32 by rprieur           #+#    #+#             */
/*   Updated: 2026/05/07 03:27:21 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool
	get_subtemplate_range(
		t_mlem_subtemplate subtemplate, t_mlem_value array)
{
	size_t	i;

	i = 0;
	while (i < array.array_len && array.array_v[i].type == MLEM_TYPE_STRING)
		i++;
	if (i < array.array_len)
		return (false);
	subtemplate.array_v = array.array_v;
	return (true);
}

bool
	get_subtemplate_keys(
		t_mlem_subtemplate subtemplate, t_mlem_value array)
{
	size_t	i;

	i = 0;
	while (i < array.array_len && array.array_v[i].type == MLEM_TYPE_STRING)
		i++;
	if (i < array.array_len)
		return (false);
	subtemplate.array_v = array.array_v;
	return (true);
}

bool
	get_subtemplate_data(
		t_mlem_subtemplate subtemplate, t_mlem_value value)
{
	if (value.type != MLEM_TYPE_ARRAY)
		return (false);
	(void)subtemplate;
	return (false);
}

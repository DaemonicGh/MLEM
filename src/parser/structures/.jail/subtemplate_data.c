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

/*
#include "parser.h"

bool
	get_subtemplate_range(
		t_mlem_subtemplate subtemplate, t_mlem_value array)
{
	size_t	i;

	i = 0;
	while (i < array.arrayv.len
		&& array.arrayv.value[i].type == MLEM_TYPE_STRING)
		i++;
	if (i < array.arrayv.len)
		return (false);
	subtemplate.arrayv.value = array.arrayv.value;
	return (true);
}

bool
	get_subtemplate_keys(
		t_mlem_subtemplate subtemplate, t_mlem_value array)
{
	size_t	i;

	i = 0;
	while (i < array.arrayv.len
		&& array.arrayv.value[i].type == MLEM_TYPE_STRING)
		i++;
	if (i < array.arrayv.len)
		return (false);
	subtemplate.arrayv.value = array.arrayv.value;
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
*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subtemplate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 21:33:40 by rprieur           #+#    #+#             */
/*   Updated: 2026/05/09 22:33:44 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "extras.h"

static bool
	print_special_value_subtemplate(t_mlem_serializer *mlem,
		t_mlem_subtemplate subtemplate)
{
	size_t		i;

	if (subtemplate.array_len != 1 || subtemplate.type & ~TYPEG_CTN_RANGE_SPE)
		return (false);
	i = 0;
	subtemplate = mlem_dereference(subtemplate.array_v[0]);
	if (subtemplate.array_len != 2)
		return (false);
	while (g_subtemplates[i].type
		&& !(subtemplate.type == g_subtemplates[i].type
			&& subtemplate.array_v[0].int_v == g_subtemplates[i].range[0]
			&& subtemplate.array_v[1].int_v == g_subtemplates[i].range[1]))
		i++;
	if (!g_subtemplates[i].type)
		return (false);
	print_tab(mlem);
	fputs(g_subtemplates[i].triggers[0], mlem->file);
	return (true);
}

static void
	print_value_subtemplate(t_mlem_serializer *mlem,
		t_mlem_subtemplate subtemplate)
{
	size_t		i;

	if (print_special_value_subtemplate(mlem, subtemplate))
		return ;
	i = 0;
	while (g_subtemplates[i].type && subtemplate.type != g_subtemplates[i].type)
		i++;
	print_tab(mlem);
	if (g_subtemplates[i].type)
	{
		fputs(g_subtemplates[i].triggers[0], mlem->file);
		if (subtemplate.type & TYPEG_CTN_RANGE)
		{
			mlem->preceded = true;
			print_value(mlem, subtemplate);
		}
	}
	else
		fwrite("???\n", 1, 4, mlem->file);
}

void
	print_subtemplate(t_mlem_serializer *mlem,
		t_mlem_subtemplate subtemplate)
{
	if (subtemplate.type & TYPEG_CONTAINER)
	{
		print_value(mlem, subtemplate);
		return ;
	}
	print_value_subtemplate(mlem, subtemplate);
	fputc('\n', mlem->file);
}

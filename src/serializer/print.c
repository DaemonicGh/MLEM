/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 18:55:59 by rprieur           #+#    #+#             */
/*   Updated: 2026/05/09 22:33:18 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include ".mlem_values.h"
#include "extras.h"

void
	print_value(t_mlem_serializer *mlem, t_mlem_value value)
{
	const t_mlem_value_type	keys[3] = {
		MLEM_TYPE_OBJECT, MLEM_TYPE_ARRAY, MLEM_TYPE_PACKED_ARRAY};
	const char				bounds[4][2][6] = {
	{"[\n", "]\n"}, {"[\n", "]\n"}, {"[*\n", "]\n"}, {"???\n"}};
	const void				*funcs[3] = {
		print_object, print_array, print_packed_array};
	size_t					i;

	if (print_type_value(mlem, value))
		return ;
	i = 0;
	while (i < 3 && value.type != keys[i])
		i++;
	print_tab(mlem);
	fputs(bounds[i][0], mlem->file);
	if (i == 3)
		return ;
	((void (*)(t_mlem_serializer *, t_mlem_value))
		(funcs[i]))(mlem, value);
	print_tab(mlem);
	fputs(bounds[i][1], mlem->file);
}

void
	mlem_print(FILE *file, t_mlem_value value)
{
	t_mlem_serializer	mlem;

	mlem = (t_mlem_serializer){0};
	mlem.file = file;
	if (value.type == MLEM_TYPE_OBJECT)
	{
		mlem.depth = -1;
		print_object(&mlem, value);
	}
	else if (value.type == MLEM_TYPE_ARRAY)
	{
		mlem.depth = -1;
		print_array(&mlem, value);
	}
	else
		print_value(&mlem, value);
}

bool
	mlem_print_to_file(const char *filename, t_mlem_value value)
{
	FILE	*file;

	file = fopen(filename, "w+");
	if (!file)
		return (false);
	mlem_print(file, value);
	fclose(file);
	return (true);
}

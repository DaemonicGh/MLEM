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

#include "extras.h"

void
	print_value(t_mlem_serializer *mlem, t_mlem_value value)
{
	if (value.type == MLEM_TYPE_OBJECT)
	{
		print_tab(mlem);
		fwrite("[\n", 1, 2, mlem->file);
		print_object(mlem, value);
		print_tab(mlem);
		fwrite("]\n", 1, 2, mlem->file);
	}
	else if (value.type == MLEM_TYPE_ARRAY)
	{
		print_tab(mlem);
		fwrite("[\n", 1, 2, mlem->file);
		print_array(mlem, value);
		print_tab(mlem);
		fwrite("]\n", 1, 2, mlem->file);
	}
	else if (value.type == MLEM_TYPE_TEMPLATE)
		print_template(mlem, value);
	else if (!print_type_value(mlem, value))
	{
		print_tab(mlem);
		fwrite("???\n", 1, 4, mlem->file);
	}
}

void
	mlem_print(FILE *file, t_mlem_value value)
{
	t_mlem_serializer	mlem;

	mlem.file = file;
	mlem.depth = -1;
	mlem.preceded = false;
	if (value.type == MLEM_TYPE_OBJECT)
		print_object(&mlem, value);
	else if (value.type == MLEM_TYPE_ARRAY)
		print_array(&mlem, value);
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

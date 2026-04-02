/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   da.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 13:59:06 by rprieur           #+#    #+#             */
/*   Updated: 2026/04/02 14:00:37 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "mlem.h"
#include "structures.h"

t_mlem_array
	da_new(void)
{
	return (ds_new(sizeof(t_mlem_value)).array);
}

bool
	da_append(t_mlem_array *array, t_mlem_value ele)
{
	t_mlem_structure	*structure;

	structure = (t_mlem_structure *)array;
	if (array->len == array->capacity
		&& !ds_resize(structure, array->capacity * DS_GROW_RATIO))
		return (false);
	array->data[array->len++] = ele;
	array->data[array->len] = (t_mlem_value){0};
	return (true);
}

void
	da_destroy(t_mlem_array *array, bool free_strings)
{
	size_t	i;

	i = 0;
	while (i < array->len)
	{
		mlem_destroy_value(&array->data[i], free_strings);
		i++;
	}
	free(array->data);
}

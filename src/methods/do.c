/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do.c                                               :+:      :+:    :+:   */
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

t_mlem_object
	do_new(void)
{
	return (ds_new(sizeof(t_mlem_pair)).object);
}

bool
	do_append(t_mlem_object *object, t_mlem_pair ele)
{
	t_mlem_structure	*structure;

	structure = (t_mlem_structure *)object;
	if (object->len == object->capacity
		&& !ds_resize(structure, object->capacity * DS_GROW_RATIO))
		return (false);
	object->data[object->len++] = ele;
	object->data[object->len] = (t_mlem_pair){0};
	return (true);
}

void
	do_destroy(t_mlem_object *object, bool free_strings)
{
	size_t	i;

	i = 0;
	while (i < object->len)
	{
		if (free_strings)
			free(object->data[i].key);
		mlem_destroy_value(&object->data[i].value, free_strings);
		i++;
	}
	free(object->data);
}

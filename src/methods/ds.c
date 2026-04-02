/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ds.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 13:59:06 by rprieur           #+#    #+#             */
/*   Updated: 2026/04/02 14:00:37 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "structures.h"

t_mlem_structure
	ds_new(size_t ele_size)
{
	t_mlem_structure	ds;

	ds = (t_mlem_structure){0};
	ds.data = malloc((DS_BASE_CAPACITY + 1) * ele_size);
	if (!ds.data)
		return (ds);
	bzero(ds.data, ele_size);
	ds.len = 0;
	ds.capacity = DS_BASE_CAPACITY;
	ds.span = ele_size;
	return (ds);
}

bool
	ds_resize(t_mlem_structure *ds, size_t new_capacity)
{
	void			*tmp;

	tmp = reallocarray(ds->data, new_capacity + 1, ds->span);
	if (!tmp && new_capacity > ds->capacity)
		return (false);
	ds->data = tmp;
	ds->capacity = new_capacity;
	return (true);
}

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

#include "structures.h"
#include "utils.h"

t_mlem_structure
	ds_new(size_t ele_size)
{
	t_mlem_structure	ds;

	ds = (t_mlem_structure){0};
	ds.raw.data = malloc((DS_BASE_CAPACITY + 1) * ele_size);
	if (!ds.raw.data)
		return (ds);
	mlem_bzero(ds.raw.data, ele_size);
	ds.raw.len = 0;
	ds.raw.capacity = DS_BASE_CAPACITY;
	ds.raw.span = ele_size;
	return (ds);
}

bool
	ds_resize(t_mlem_structure *ds, size_t new_capacity)
{
	void			*tmp;

	tmp = reallocarray(ds->raw.data, new_capacity + 1, ds->raw.span);
	if (!tmp && new_capacity > ds->raw.capacity)
		return (false);
	ds->raw.data = tmp;
	ds->raw.capacity = new_capacity;
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 13:59:06 by rprieur           #+#    #+#             */
/*   Updated: 2026/05/09 02:39:19 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdlib.h>

#include "data.h"
#include "mlem.h"

bool
	mlem_object_resize(t_mlem_value *object, uint32_t new_capacity)
{
	void	*tmp;

	if (new_capacity > object->object_len + UINT16_MAX)
		new_capacity = object->object_len + UINT16_MAX;
	object = mlem_dereference_ptr(object);
	tmp = realloc(object->object_v, sizeof(t_mlem_pair) * new_capacity);
	if (!tmp)
		return (false);
	object->object_v = tmp;
	if (new_capacity > object->object_len)
		object->object_extra_capacity = new_capacity - object->object_len;
	else
		object->object_extra_capacity = 0;
	return (true);
}

bool
	mlem_object_append(
		t_mlem_value *object, t_mlem_string key, t_mlem_value value)
{
	object = mlem_dereference_ptr(object);
	if (object->object_extra_capacity == 0)
	{
		if (!mlem_object_resize(
				object, object->object_len * STRUCTURE_GROW_RATIO))
			return (false);
	}
	object->object_v[object->object_len] = (t_mlem_pair){
		.key = key, .value = value};
	object->object_len++;
	object->object_extra_capacity--;
	return (true);
}

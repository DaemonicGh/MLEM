/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 13:59:06 by rprieur           #+#    #+#             */
/*   Updated: 2026/05/04 18:19:46 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdlib.h>

#include "extras.h"
#include "mlem.h"

bool
	mlem_packed_array_resize(t_mlem_value *array, uint32_t new_capacity)
{
	void	*tmp;

	array = mlem_dereference_ptr(array);
	if (new_capacity > array->packedv.len + UINT16_MAX)
		new_capacity = array->packedv.len + UINT16_MAX;
	tmp = realloc(array->packedv.value_ptr,
			get_type_size(array->packedv.element_type) * new_capacity);
	if (!tmp)
		return (false);
	array->packedv.value_ptr = tmp;
	if (new_capacity > array->packedv.len)
		array->packedv.extra_capacity = new_capacity - array->packedv.len;
	else
		array->packedv.extra_capacity = 0;
	return (true);
}

bool
	mlem_packed_array_append(t_mlem_value *array, t_mlem_value value)
{
	array = mlem_dereference_ptr(array);
	if (array->packedv.extra_capacity == 0)
	{
		if (!mlem_packed_array_resize(array,
				array->packedv.len * STRUCTURE_GROW_RATIO))
			return (false);
	}
	array->packedv.len++;
	if (!mlem_packed_array_set(*array, array->packedv.len - 1, value))
		return (false);
	array->packedv.extra_capacity--;
	return (true);
}

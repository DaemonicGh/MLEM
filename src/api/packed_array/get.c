/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 21:44:40 by rprieur           #+#    #+#             */
/*   Updated: 2026/05/04 18:19:58 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include ".mlem_values.h"
#include "mlem.h"

t_mlem_value
	mlem_packed_array_get(t_mlem_value array, uint32_t index)
{
	array = mlem_dereference(array);
	if (index >= array.packedv.len)
		return ((t_mlem_value){0});
	if (array.packedv.element_type == MLEM_TYPE_FLOAT)
		return (mlem_float(array.packedv.value_float[index]));
	if (array.packedv.element_type == MLEM_TYPE_BOOL)
		return (mlem_bool(array.packedv.value_bool[index]));
	return (mlem_raw_value(array.packedv.element_type,
			(uint64_t)array.packedv.value_ptr[index]));
}

int64_t
	mlem_packed_array_index(t_mlem_value array, t_mlem_value value)
{
	int64_t	i;

	array = mlem_dereference(array);
	if (!mlem_tweak(&value, array.packedv.element_type))
		return (-1);
	i = 0;
	if (value.type == MLEM_TYPE_BOOL)
	{
		while (i < array.packedv.len)
		{
			if (array.packedv.value_bool[i] == value.boolv.value)
				return (i);
			i++;
		}
		return (-1);
	}
	while (i < array.packedv.len)
	{
		if ((value.type == MLEM_TYPE_FLOAT
				&& array.packedv.value_float[i] == value.floatv.value)
			|| array.packedv.value_int[i] == value.intv.value)
			return (i);
		i++;
	}
	return (-1);
}

bool
	mlem_packed_array_set(
		t_mlem_value array, uint32_t index, t_mlem_value value)
{
	array = mlem_dereference(array);
	if (index >= array.packedv.len
		|| !mlem_tweak(&value, array.packedv.element_type))
		return (false);
	if (value.type == MLEM_TYPE_FLOAT)
		array.packedv.value_float[index] = value.floatv.value;
	else if (value.type == MLEM_TYPE_BOOL)
		array.packedv.value_bool[index] = value.boolv.value;
	else
		array.packedv.value_int[index] = value.intv.value;
	return (true);
}

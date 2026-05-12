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

#include "data.h"
#include "mlem.h"

bool
	mlem_array_resize(t_mlem_value *array, uint32_t new_capacity)
{
	void	*tmp;

	if (new_capacity > array->array_len + UINT16_MAX)
		new_capacity = array->array_len + UINT16_MAX;
	array = mlem_dereference_ptr(array);
	tmp = realloc(array->array_v, sizeof(t_mlem_value) * new_capacity);
	if (!tmp)
		return (false);
	array->array_v = tmp;
	if (new_capacity > array->array_len)
		array->array_extra_capacity = new_capacity - array->array_len;
	else
		array->array_extra_capacity = 0;
	return (true);
}

bool
	mlem_array_append(t_mlem_value *array, t_mlem_value value)
{
	array = mlem_dereference_ptr(array);
	if (array->array_extra_capacity == 0)
	{
		if (!mlem_array_resize(array, array->array_len * STRUCTURE_GROW_RATIO))
			return (false);
	}
	array->array_v[array->array_len] = value;
	array->array_len++;
	array->array_extra_capacity--;
	return (true);
}

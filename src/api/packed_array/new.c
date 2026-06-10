/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 18:31:27 by rprieur           #+#    #+#             */
/*   Updated: 2026/05/04 18:20:04 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdarg.h>

#include "extras.h"

t_mlem_value
	mlem_packed_array_empty(t_mlem_value_type type, uint32_t capacity)
{
	t_mlem_value	array;

	if (!is_valid_packed_type(type))
		return ((t_mlem_value){0});
	array.type = MLEM_TYPE_PACKED_ARRAY;
	array.packedv.element_type = type;
	array.packedv.value_ptr = malloc(get_type_size(type) * capacity);
	if (!array.packedv.value_ptr)
		return ((t_mlem_value){0});
	array.packedv.len = 0;
	array.packedv.extra_capacity = capacity;
	return (array);
}

t_mlem_value
	mlem_packed_array(t_mlem_value_type type, uint32_t len, ...)
{
	t_mlem_value	array;
	va_list			va;
	size_t			i;

	array = mlem_packed_array_empty(type, len);
	if (!array.type)
		return ((t_mlem_value){0});
	i = 0;
	va_start(va, len);
	if (type == MLEM_TYPE_INT)
		while (i < len)
			array.packedv.value_int[i++] = va_arg(va, t_mlem_int);
	if (type == MLEM_TYPE_FLOAT)
		while (i < len)
			array.packedv.value_float[i++] = va_arg(va, t_mlem_float);
	else if (type == MLEM_TYPE_BOOL)
		while (i < len)
			array.packedv.value_bool[i++] = va_arg(va, int);
	else
		while (i < len)
			array.packedv.value_ptr[i++] = va_arg(va, void *);
	va_end(va);
	array.packedv.len = len;
	return (array);
}

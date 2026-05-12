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

#include "mlem.h"

t_mlem_value
	mlem_array_empty(uint32_t capacity)
{
	t_mlem_value	array;

	array.type = MLEM_TYPE_ARRAY;
	array.array_v = malloc(sizeof(t_mlem_value) * capacity);
	if (!array.array_v)
		return ((t_mlem_value){0});
	array.array_len = 0;
	array.array_extra_capacity = capacity;
	return (array);
}

t_mlem_value
	mlem_array(uint32_t len, ...)
{
	t_mlem_value	array;
	va_list			va;
	size_t			i;

	array = mlem_array_empty(len);
	if (!array.type)
		return ((t_mlem_value){0});
	i = 0;
	va_start(va, len);
	while (i < len)
		array.array_v[i++] = va_arg(va, t_mlem_value);
	va_end(va);
	return (array);
}

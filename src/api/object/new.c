/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 18:31:30 by rprieur           #+#    #+#             */
/*   Updated: 2026/05/04 18:20:51 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdarg.h>

#include "mlem.h"

t_mlem_value
	mlem_object_empty(uint32_t capacity)
{
	t_mlem_value	object;

	object.type = MLEM_TYPE_OBJECT;
	object.object_v = malloc(sizeof(t_mlem_pair) * capacity);
	if (!object.object_v)
		return ((t_mlem_value){0});
	object.object_len = 0;
	object.object_extra_capacity = capacity;
	return (object);
}

t_mlem_value
	mlem_object(uint32_t len, ...)
{
	t_mlem_value	object;
	va_list			va;
	size_t			i;

	object = mlem_object_empty(len);
	if (!object.type)
		return ((t_mlem_value){0});
	i = 0;
	va_start(va, len);
	while (i < len)
		object.object_v[i++] = va_arg(va, t_mlem_pair);
	va_end(va);
	return (object);
}

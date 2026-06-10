/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   value.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 21:33:03 by rprieur           #+#    #+#             */
/*   Updated: 2026/05/08 18:49:14 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdio.h>

#include "mlem.h"

t_mlem_value_type
	mlem_type(t_mlem_value value)
{
	return (mlem_dereference(value).type);
}

bool
	mlem_is_type(t_mlem_value value, uint32_t count, ...)
{
	va_list		va;
	uint32_t	i;

	value = mlem_dereference(value);
	i = 0;
	va_start(va, count);
	while (i < count)
	{
		if (value.type == va_arg(va, int))
		{
			va_end(va);
			return (true);
		}
		i++;
	}
	va_end(va);
	return (false);
}

bool
	mlem_equal(t_mlem_value value1, t_mlem_value value2)
{
	value1 = mlem_dereference(value1);
	value2 = mlem_dereference(value2);
	if (value1.type != value2.type)
		return (false);
	if (value1.type == MLEM_TYPE_FLOAT
		&& value1.floatv.value == value2.floatv.value)
		return (true);
	return (value1.intv.value == value2.intv.value);
}

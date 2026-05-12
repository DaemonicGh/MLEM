/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 21:53:16 by rprieur           #+#    #+#             */
/*   Updated: 2026/05/09 02:38:19 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlem.h"

bool
	mlem_tweak(t_mlem_value *value, t_mlem_value_type type)
{
	if (type == MLEM_TYPE_INT)
	{
		if (value->type == MLEM_TYPE_FLOAT
			&& (t_mlem_int)value->float_v == value->float_v)
			*value = mlem_int(value->float_v);
		else if (value->type == MLEM_TYPE_BOOL)
			*value = mlem_int(value->bool_v);
	}
	else if (type == MLEM_TYPE_FLOAT)
	{
		if (value->type == MLEM_TYPE_INT)
			*value = mlem_float(value->int_v);
		else if (value->type == MLEM_TYPE_BOOL)
			*value = mlem_float(value->bool_v);
	}
	return (value->type == type);
}

bool
	mlem_convert(t_mlem_value *value, t_mlem_value_type type)
{
	if (mlem_tweak(value, type))
		return (true);
	if (type == MLEM_TYPE_INT)
	{
		if (value->type == MLEM_TYPE_FLOAT)
			*value = mlem_int(value->float_v);
	}
	else if (type == MLEM_TYPE_BOOL)
	{
		if (value->type == MLEM_TYPE_INT)
			*value = mlem_bool(value->int_v);
		else if (value->type == MLEM_TYPE_FLOAT)
			*value = mlem_bool(value->float_v);
	}
	return (value->type == type);
}

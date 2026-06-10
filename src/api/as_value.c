/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 00:35:38 by rprieur           #+#    #+#             */
/*   Updated: 2026/06/02 00:35:38 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlem.h"

t_mlem_int
	mlem_as_int(t_mlem_value *value, t_mlem_int fallback)
{
	if (!value)
		return (fallback);
	value = mlem_dereference_ptr(value);
	if (mlem_tweak(value, MLEM_TYPE_INT))
		return (value->intv.value);
	else
		return (fallback);
}

t_mlem_float
	mlem_as_float(t_mlem_value *value, t_mlem_float fallback)
{
	if (!value)
		return (fallback);
	value = mlem_dereference_ptr(value);
	if (mlem_tweak(value, MLEM_TYPE_FLOAT))
		return (value->floatv.value);
	else
		return (fallback);
}

t_mlem_bool
	mlem_as_bool(t_mlem_value *value, t_mlem_bool fallback)
{
	if (!value)
		return (fallback);
	value = mlem_dereference_ptr(value);
	if (mlem_tweak(value, MLEM_TYPE_BOOL))
		return (value->boolv.value);
	else
		return (fallback);
}

t_mlem_string
	mlem_as_string(t_mlem_value *value, t_mlem_string fallback)
{
	if (!value)
		return (fallback);
	value = mlem_dereference_ptr(value);
	if (mlem_tweak(value, MLEM_TYPE_STRING))
		return (value->strv.value);
	else
		return (fallback);
}

t_mlem_value
	mlem_fallback(t_mlem_value *value, t_mlem_value fallback)
{
	if (!value)
		return (fallback);
	value = mlem_dereference_ptr(value);
	if (value->type != fallback.type)
		return (fallback);
	else
		return (*value);
}

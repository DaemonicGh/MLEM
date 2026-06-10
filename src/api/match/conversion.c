/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 21:53:16 by rprieur           #+#    #+#             */
/*   Updated: 2026/05/02 02:39:59 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include "mlem.h"
#include "extras.h"

bool
	try_tweak(t_mlem_candidate *candidate, t_mlem_subtemplate subtemplate)
{
	if (subtemplate.type == MLEM_TYPE_INT)
	{
		if (candidate->value.type == MLEM_TYPE_FLOAT
			&& (t_mlem_int)candidate->value.floatv.value
			== candidate->value.floatv.value)
			candidate->value.intv.value = candidate->value.floatv.value;
		else
			return (false);
	}
	else if (subtemplate.type == MLEM_TYPE_FLOAT)
	{
		if (candidate->value.type == MLEM_TYPE_INT)
			candidate->value.floatv.value = candidate->value.intv.value;
		else
			return (false);
	}
	else
		return (false);
	candidate->value.type = subtemplate.type;
	return (true);
}

static bool
	try_conversion2(t_mlem_candidate *candidate, t_mlem_subtemplate subtemplate)
{
	if (subtemplate.type == MLEM_TYPE_BOOL)
	{
		if (candidate->value.type == MLEM_TYPE_INT)
			candidate->value.boolv.value = candidate->value.intv.value;
		else if (candidate->value.type == MLEM_TYPE_FLOAT)
			candidate->value.intv.value = candidate->value.floatv.value;
		else
			return (false);
	}
	else
		return (false);
	return (true);
}

bool
	try_conversion(t_mlem_candidate *candidate, t_mlem_subtemplate subtemplate)
{
	if (subtemplate.type == MLEM_TYPE_INT)
	{
		if (candidate->value.type == MLEM_TYPE_FLOAT)
			candidate->value.intv.value = candidate->value.floatv.value;
		else if (candidate->value.type == MLEM_TYPE_BOOL)
			candidate->value.intv.value = candidate->value.boolv.value;
		else
			return (false);
	}
	else if (subtemplate.type == MLEM_TYPE_FLOAT)
	{
		if (candidate->value.type == MLEM_TYPE_BOOL)
			candidate->value.floatv.value = candidate->value.boolv.value;
		else
			return (false);
	}
	else if (!try_conversion2(candidate, subtemplate))
		return (false);
	candidate->value.type = subtemplate.type;
	candidate->weight |= CANDF_CONVERTED;
	return (true);
}
*/

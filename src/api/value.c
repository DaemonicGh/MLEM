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

#include "mlem.h"
#include <math.h>

t_mlem_value_type
	mlem_type(t_mlem_value value)
{
	return (mlem_dereference(value).type);
}

bool
	mlem_equal(t_mlem_value value1, t_mlem_value value2)
{
	value1 = mlem_dereference(value1);
	value2 = mlem_dereference(value2);
	if (value1.type != value2.type)
		return (false);
	if (value1.type == MLEM_TYPE_FLOAT && value1.float_v == value2.float_v)
		return (true);
	return (value1.int_v == value2.int_v);
}

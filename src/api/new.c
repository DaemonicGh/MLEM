/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 17:53:45 by rprieur           #+#    #+#             */
/*   Updated: 2026/05/08 17:26:12 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlem.h"
#include "extras.h"

t_mlem_value
	mlem_int(t_mlem_int value)
{
	return ((t_mlem_value){
		.type = MLEM_TYPE_INT,
		.int_base = 10,
		.int_v = value
	});
}

t_mlem_value
	mlem_float(t_mlem_float value)
{
	return ((t_mlem_value){
		.type = MLEM_TYPE_FLOAT,
		.float_exponent = 0,
		.float_v = value
	});
}

t_mlem_value
	mlem_bool(t_mlem_bool value)
{
	return ((t_mlem_value){
		.type = MLEM_TYPE_BOOL,
		.bool_v = value
	});
}

t_mlem_value
	mlem_string(t_mlem_string value)
{
	return ((t_mlem_value){
		.type = MLEM_TYPE_STRING,
		.string_flavor = MLEM_STR_DQUOTED,
		.string_extra_capacity = 0,
		.string_len = mlem_strlen(value),
		.string_v = value
	});
}

t_mlem_value
	mlem_null(void)
{
	return ((t_mlem_value){
		.type = MLEM_TYPE_NULL
	});
}

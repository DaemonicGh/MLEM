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
		.intv = {
			.type = MLEM_TYPE_INT,
			.base = 10,
			.value = value
		}
	});
}

t_mlem_value
	mlem_float(t_mlem_float value)
{
	return ((t_mlem_value){
		.floatv = {
			.type = MLEM_TYPE_FLOAT,
			.exponent = 0,
			.value = value
		}
	});
}

t_mlem_value
	mlem_bool(t_mlem_bool value)
{
	return ((t_mlem_value){
		.boolv = {
			.type = MLEM_TYPE_BOOL,
			.value = value
		}
	});
}

t_mlem_value
	mlem_string(t_mlem_string value)
{
	return ((t_mlem_value){
		.strv = {
			.type = MLEM_TYPE_STRING,
			.flavor = MLEM_STR_DQUOTED,
			.extra_capacity = 0,
			.len = mlem_strlen(value),
			.value = value
		}
	});
}

t_mlem_value
	mlem_null(void)
{
	return ((t_mlem_value){
		.type = MLEM_TYPE_NULL
	});
}

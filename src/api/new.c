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

#include ".mlem_values.h"
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
	mlem_string_ex(t_mlem_string value, uint32_t len, uint8_t flavor)
{
	return ((t_mlem_value){
		.strv = {
			.type = MLEM_TYPE_STRING,
			.flavor = flavor,
			.extra_capacity = 0,
			.len = len,
			.value = value
		}
	});
}

t_mlem_value
	mlem_string(t_mlem_string value)
{
	uint32_t	len;
	uint8_t		flavor;

	if (!value[0])
		return (mlem_string_ex(value, 0, MLEM_STR_DQUOTED));
	if ((value[0] < 'a' || value[0] > 'z')
		&& (value[0] < 'A' || value[0] > 'Z')
		&& value[0] != '_')
		flavor = MLEM_STR_DQUOTED;
	else
		flavor = MLEM_STR_UNQUOTED;
	len = 1;
	while (value[len] && flavor == MLEM_STR_UNQUOTED)
	{
		if ((value[len] < 'a' || value[len] > 'z')
			&& (value[len] < 'A' || value[len] > 'Z')
			&& (value[len] < '0' || value[len] > '9')
			&& value[len] != '_')
			flavor = MLEM_STR_DQUOTED;
		len++;
	}
	while (value[len])
		len++;
	return (mlem_string_ex(value, len, flavor));
}

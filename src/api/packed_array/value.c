/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   value.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 20:41:10 by rprieur           #+#    #+#             */
/*   Updated: 2026/06/10 20:41:10 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlem.h"

bool	is_valid_packed_type(t_mlem_value_type type)
{
	return (
		type && type != MLEM_TYPE_NULL
		&& !(type & MLEM_TYPE_MASK_CONTAINS_ARRAY)
	);
}

size_t	get_type_size(t_mlem_value_type type)
{
	if (!type || type == MLEM_TYPE_NULL)
		return (0);
	if (type == MLEM_TYPE_INT)
		return (sizeof(t_mlem_int));
	if (type == MLEM_TYPE_FLOAT)
		return (sizeof(t_mlem_float));
	if (type == MLEM_TYPE_BOOL)
		return (sizeof(t_mlem_bool));
	return (sizeof(void *));
}

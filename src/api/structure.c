/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 20:53:28 by rprieur           #+#    #+#             */
/*   Updated: 2026/05/09 02:46:01 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlem.h"

uint32_t
	mlem_length(t_mlem_value value)
{
	return (mlem_dereference(value).array_len);
}

bool
	mlem_append(t_mlem_value *structure,
		t_mlem_string key, t_mlem_value value)
{
	if (structure->type == MLEM_TYPE_ARRAY)
		return (mlem_array_append(structure, value));
	else if (structure->type == MLEM_TYPE_OBJECT)
		return (mlem_object_append(structure, key, value));
	else if (structure->type == MLEM_TYPE_TEMPLATE)
		return (mlem_template_append(structure, value));
	return (false);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 21:48:25 by rprieur           #+#    #+#             */
/*   Updated: 2026/05/04 18:22:34 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "extras.h"

void
	destroy_reference(t_mlem_value reference,
		bool free_keys, bool free_strings, bool free_ref_names)
{
	reference.refv.value->ref_count--;
	if (reference.refv.value->ref_count == 0)
	{
		if (free_ref_names)
			free(reference.refv.value->name);
		mlem_destroy_ex(reference.refv.value->value,
			free_keys, free_strings, free_ref_names);
		free(reference.refv.value);
	}
}

void
	mlem_destroy_ex(t_mlem_value value,
		bool free_keys, bool free_strings, bool free_ref_names)
{
	if (value.type == MLEM_TYPE_STRING)
	{
		if (free_strings)
			free(value.strv.value);
	}
	else if (value.type == MLEM_TYPE_REFERENCE)
		destroy_reference(value, free_keys, free_strings, free_ref_names);
	else if (value.type == MLEM_TYPE_ARRAY)
		destroy_array(value, free_keys, free_strings, free_ref_names);
	else if (value.type == MLEM_TYPE_PACKED_ARRAY)
		destroy_packed_array(value, free_keys, free_strings, free_ref_names);
	else if (value.type == MLEM_TYPE_OBJECT)
		destroy_object(value, free_keys, free_strings, free_ref_names);
}

void
	mlem_destroy(t_mlem_value value)
{
	mlem_destroy_ex(value, true, true, true);
}

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

#include ".mlem_values.h"
#include "extras.h"
#include "mlem.h"

void
	destroy_array(t_mlem_value array,
		bool free_keys, bool free_strings, bool free_ref_names)
{
	size_t	i;

	i = 0;
	while (i < array.arrayv.len)
	{
		mlem_destroy_ex(array.arrayv.value[i],
			free_keys, free_strings, free_ref_names);
		i++;
	}
	free(array.arrayv.value);
}

void
	destroy_packed_array(t_mlem_value array,
		bool free_keys, bool free_strings, bool free_ref_names)
{
	size_t	i;

	i = 0;
	if (free_strings && array.packedv.element_type == MLEM_TYPE_STRING)
		while (i < array.packedv.len)
			free(array.packedv.value_str[i++]);
	else if (array.packedv.element_type == MLEM_TYPE_REFERENCE)
		while (i < array.packedv.len)
			destroy_reference(mlem_raw_value(array.packedv.element_type,
					(uint64_t)array.packedv.value_ref[i++]),
				free_keys, free_strings, free_ref_names);
	free(array.packedv.value_ptr);
}

void
	destroy_object(t_mlem_value object,
		bool free_keys, bool free_strings, bool free_ref_names)
{
	size_t	i;

	i = 0;
	while (i < object.objectv.len)
	{
		if (free_keys
			&& (object.objectv.value[i].value.type != MLEM_TYPE_REFERENCE
				|| !object.objectv.value[i].value.refv.is_owner))
			free(object.objectv.value[i].key);
		mlem_destroy_ex(object.objectv.value[i].value,
			free_keys, free_strings, free_ref_names);
		i++;
	}
	free(object.objectv.value);
}

/*
void
	destroy_template(t_mlem_value template)
{
	size_t	i;

	i = 0;
	if (template.template_v->fallback.type)
		destroy_reference((t_mlem_value){.type = MLEM_TYPE_REFERENCE,
			.refv.value = template.template_v->fallback.refv.value});
	if (template.template_v->structure.type)
		destroy_array(template.template_v->structure);
	while (i < template.template_len)
	{
		if (template.template_v->subtemplates[i].type & TYPEG_CONTAINER)
			mlem_destroy(template.template_v->subtemplates[i]);
		else if (template.template_v->subtemplates[i].type & TYPEG_CTN_RANGE)
			destroy_array(template.template_v->subtemplates[i]);
		i++;
	}
	free(template.template_v);
}
*/

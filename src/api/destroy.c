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

#include "mlem.h"

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
	else if (value.type == MLEM_TYPE_OBJECT)
		destroy_object(value, free_keys, free_strings, free_ref_names);
}

void
	mlem_destroy(t_mlem_value value)
{
	mlem_destroy_ex(value, true, true, true);
}

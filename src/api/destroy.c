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

#include "data.h"
#include "mlem.h"

void
	destroy_reference(t_mlem_value reference)
{
	reference.reference_v->ref_count--;
	if (reference.reference_v->ref_count == 0)
	{
		free(reference.reference_v->name);
		mlem_destroy(reference.reference_v->value);
		free(reference.reference_v);
	}
}

void
	destroy_array(t_mlem_value array)
{
	size_t	i;

	i = 0;
	while (i < array.array_len)
	{
		mlem_destroy(array.array_v[i]);
		i++;
	}
	free(array.array_v);
}

void
	destroy_object(t_mlem_value object)
{
	size_t	i;

	i = 0;
	while (i < object.object_len)
	{
		if (object.object_v[i].value.type != MLEM_TYPE_REFERENCE
			|| !object.object_v[i].value.reference_owner)
			free(object.object_v[i].key);
		mlem_destroy(object.object_v[i].value);
		i++;
	}
	free(object.object_v);
}

void
	destroy_template(t_mlem_value template)
{
	size_t	i;

	i = 0;
	if (template.template_v->fallback.type)
		destroy_reference((t_mlem_value){.type = MLEM_TYPE_REFERENCE,
			.reference_v = template.template_v->fallback.reference_v});
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

void
	mlem_destroy(t_mlem_value value)
{
	if (value.type == MLEM_TYPE_STRING)
		free(value.string_v);
	else if (value.type == MLEM_TYPE_REFERENCE)
		destroy_reference(value);
	else if (value.type == MLEM_TYPE_ARRAY)
		destroy_array(value);
	else if (value.type == MLEM_TYPE_OBJECT)
		destroy_object(value);
	else if (value.type == MLEM_TYPE_TEMPLATE)
		destroy_template(value);
}

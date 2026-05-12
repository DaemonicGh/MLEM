/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 21:48:12 by rprieur           #+#    #+#             */
/*   Updated: 2026/05/09 23:09:01 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "data.h"
#include "extras.h"

static t_mlem_value
	copy_array(t_mlem_value array)
{
	t_mlem_value	new;

	new = mlem_array_empty(array.array_len);
	if (!new.type)
		return ((t_mlem_value){0});
	while (new.array_len < array.array_len)
	{
		new.array_v[new.array_len] = mlem_copy(array.array_v[new.array_len]);
		if (!new.array_v[new.array_len].type)
		{
			mlem_destroy(new);
			return ((t_mlem_value){0});
		}
		new.array_len++;
	}
	return (new);
}

static t_mlem_value
	copy_object(t_mlem_value object)
{
	t_mlem_value	new;

	new = mlem_object_empty(object.object_len);
	if (!new.type)
		return ((t_mlem_value){0});
	while (new.object_len < object.object_len)
	{
		new.object_v[new.object_len].key = mlem_strdup(
				object.object_v[new.object_len].key);
		new.object_v[new.object_len].value = mlem_copy(
				object.object_v[new.object_len].value);
		if (!new.object_v[new.object_len].key
			|| !new.object_v[new.object_len].value.type)
		{
			free(new.object_v[new.object_len].key);
			mlem_destroy(new);
			return ((t_mlem_value){0});
		}
		new.object_len++;
	}
	return (new);
}

static t_mlem_value
	copy_subtemplate(t_mlem_subtemplate subtemplate)
{
	t_mlem_value	new;

	if (subtemplate.type & TYPEG_CONTAINER)
		return (mlem_copy(subtemplate));
	else if (subtemplate.type & TYPEG_CTN_RANGE)
	{
		new = copy_array(subtemplate);
		if (!new.type)
			return ((t_mlem_value){0});
		new.type = subtemplate.type;
		return (new);
	}
	return (subtemplate);
}

static t_mlem_value
	copy_template(t_mlem_value template)
{
	t_mlem_value	new;

	new = mlem_template_empty(template.template_len);
	if (!new.type)
		return ((t_mlem_value){0});
	new.template_v->flags = template.template_v->flags;
	new.template_v->fallback = template.template_v->fallback;
	template.template_v->fallback.reference_v->ref_count++;
	new.template_v->structure = copy_array(template.template_v->structure);
	if (new.template_v->structure.type)
	{
		while (new.template_len < template.template_len)
		{
			new.template_v->subtemplates[new.template_len] = copy_subtemplate(
					template.template_v->subtemplates[new.template_len]);
			if (!new.template_v->subtemplates[new.template_len].type)
				break ;
			new.template_len++;
		}
		if (new.template_len == template.template_len)
			return (new);
	}
	mlem_destroy(new);
	return ((t_mlem_value){0});
}

t_mlem_value
	mlem_copy(t_mlem_value value)
{
	if (value.type == MLEM_TYPE_STRING)
		return (mlem_string(mlem_strdup(value.string_v)));
	else if (value.type == MLEM_TYPE_REFERENCE)
	{
		value.reference_v->ref_count++;
		return (value);
	}
	else if (value.type == MLEM_TYPE_ARRAY)
		return (copy_array(value));
	else if (value.type == MLEM_TYPE_OBJECT)
		return (copy_object(value));
	else if (value.type == MLEM_TYPE_TEMPLATE)
		return (copy_template(value));
	return (value);
}

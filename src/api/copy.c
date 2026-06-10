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

#include "extras.h"

static t_mlem_value
	copy_array(t_mlem_value array)
{
	t_mlem_value	new;

	new = mlem_array_empty(array.arrayv.len);
	if (!new.type)
		return ((t_mlem_value){0});
	while (new.arrayv.len < array.arrayv.len)
	{
		new.arrayv.value[new.arrayv.len] = mlem_copy(
				array.arrayv.value[new.arrayv.len]);
		if (!new.arrayv.value[new.arrayv.len].type)
		{
			mlem_destroy(new);
			return ((t_mlem_value){0});
		}
		new.arrayv.len++;
	}
	return (new);
}

static t_mlem_value
	copy_object(t_mlem_value object)
{
	t_mlem_value	new;

	new = mlem_object_empty(object.objectv.len);
	if (!new.type)
		return ((t_mlem_value){0});
	while (new.objectv.len < object.objectv.len)
	{
		new.objectv.value[new.objectv.len].key = mlem_strdup(
				object.objectv.value[new.objectv.len].key);
		new.objectv.value[new.objectv.len].value = mlem_copy(
				object.objectv.value[new.objectv.len].value);
		if (!new.objectv.value[new.objectv.len].key
			|| !new.objectv.value[new.objectv.len].value.type)
		{
			free(new.objectv.value[new.objectv.len].key);
			mlem_destroy(new);
			return ((t_mlem_value){0});
		}
		new.objectv.len++;
	}
	return (new);
}

/*
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
	template.template_v->fallback.refv.value->ref_count++;
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
*/

t_mlem_value
	mlem_copy(t_mlem_value value)
{
	if (value.type == MLEM_TYPE_STRING)
		return (mlem_string(mlem_strdup(value.strv.value)));
	else if (value.type == MLEM_TYPE_REFERENCE)
	{
		value.refv.value->ref_count++;
		return (value);
	}
	else if (value.type == MLEM_TYPE_ARRAY)
		return (copy_array(value));
	else if (value.type == MLEM_TYPE_OBJECT)
		return (copy_object(value));
	return (value);
}

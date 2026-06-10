/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 21:53:37 by rprieur           #+#    #+#             */
/*   Updated: 2026/05/02 02:41:14 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include "mlem.h"
#include "extras.h"

static bool
	match_restrictor_values(t_mlem_value *value,
		t_mlem_template *template, t_mlem_subtemplate restrictor)
{
	size_t	i;

	i = 0;
	if (restrictor.type == MLEM_TYPE_ARRAY)
	{
		if ((t_mlem_int)value->arrayv.value->len < restrictor.data.range_i[0]
			|| (t_mlem_int)value->arrayv.value->len > restrictor.data.range_i[1])
			return (false);
		while (i < value->arrayv.value->len && mlem_match_template(
				mlem_array_get(value->arrayv.value, i), value, template))
			i++;
		return (i == value->arrayv.value->len);
	}
	if (restrictor.type == MLEM_TYPE_OBJECT)
	{
		while (i < restrictor.data.array->len
			&& mlem_match_template(mlem_object_get(value->objectv.value,
				value->arrayv.value->content[i].strv.value), value, template))
			i++;
		return (i == restrictor.data.array->len);
	}
	return (false);
}

bool
	match_restrictor(t_mlem_value *value, t_mlem_template *template)
{
	t_mlem_subtemplate	restrictor;
	bool				ret;

	if (value->type != template->restrictor.type)
		return (false);
	restrictor = template->restrictor;
	template->restrictor = (t_mlem_subtemplate){0};
	ret = match_restrictor_values(value, template, restrictor);
	template->restrictor = restrictor;
	return (ret);
}

static bool
	match_array_object(
		t_mlem_candidate *candidate, t_mlem_subtemplate subtemplate)
{
	size_t			i;

	i = 0;
	if (subtemplate.type == MLEM_TYPE_ARRAY)
	{
		while (i < subtemplate.data.array->len && mlem_match_template(
				mlem_array_get(candidate->value.arrayv.value, i),
				&candidate->value,
				subtemplate.data.array->content[i].template_v))
			i++;
		return (i == subtemplate.data.array->len);
	}
	if (subtemplate.type == MLEM_TYPE_OBJECT)
	{
		while (i < subtemplate.data.object->len && mlem_match_template(
				mlem_object_get(candidate->value.objectv.value,
					subtemplate.data.object->content[i].key),
				&candidate->value,
				subtemplate.data.object->content[i].value.template_v))
			i++;
		return (i == subtemplate.data.object->len);
	}
	return (false);
}

bool
	match_structure(t_mlem_candidate *candidate, t_mlem_subtemplate subtemplate)
{
	if (subtemplate.type == MLEM_TYPE_TEMPLATE)
		return (mlem_match_template(&candidate->value, candidate->parent,
				subtemplate.data.template));
	return (match_array_object(candidate, subtemplate));
}
*/

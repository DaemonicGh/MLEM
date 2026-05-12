/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 14:32:42 by rprieur           #+#    #+#             */
/*   Updated: 2026/05/03 20:16:22 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "mlem.h"
#include "tools.h"

static int
	early_checks(
		t_mlem_value *value, t_mlem_value *parent, t_mlem_value template)
{
	if (!template.type || template.len == 0)
		return (!(template.template_v->flags & MLEM_TPF_NO_WILDCARD));
	if (!value)
	{
		if (template.template_v->flags & MLEM_TPF_REQUIRED)
			return (false);
		if (parent && template.template_v->fallback.type)
		{
			printf("Parent before = %p\n", parent->pointer_v);
			mlem_append(parent,
				template.template_v->fallback.reference_v->name,
				template.template_v->fallback);
			template.template_v->fallback.reference_v->ref_count++;
			printf("Parent after  = %p\n", parent->pointer_v);
		}
		return (true);
	}
	return (-1);
}

static bool
	set_value(t_mlem_value *value,
		t_mlem_value template, t_mlem_candidate candidate)
{
	if (!candidate.weight)
		*mlem_dereference_ptr(value) = candidate.value;
	else if (candidate.weight & CANDF_OOB)
		return (false);
	else if (candidate.value.type)
		*mlem_dereference_ptr(value) = candidate.value;
	else if (template.template_v->fallback.type)
	{
		mlem_destroy(*value);
		*value = template.template_v->fallback;
		value->reference_v->ref_count++;
	}
	else
		return (false);
	return (true);
}

static bool
	mlem_match_subtemplate(t_mlem_value value,
		t_mlem_subtemplate subtemplate, t_mlem_template_flag flags,
		t_mlem_candidate *candidate)
{
	t_mlem_value	sub_ref;

	candidate->value = mlem_dereference(value);
	subtemplate = mlem_dereference(subtemplate);
	candidate->weight = CANDF_UNSET;
	if (subtemplate.type != MLEM_TYPE_TEMPLATE
		&& candidate->value.type != subtemplate.type
		&& ((flags & MLEM_TPF_STRICT_TYPE)
			|| !try_tweak(candidate, subtemplate))
		&& (!(flags & MLEM_TPF_CONVERT)
			|| !try_conversion(candidate, subtemplate)))
		return (false);
	candidate->weight &= ~CANDF_UNSET;
	if (subtemplate.type & TYPEG_CONTAINER)
		return (match_structure(candidate, subtemplate));
	if (((flags & MLEM_TPF_CLAMP) && clamp_bounds(candidate, subtemplate))
		|| check_bounds(candidate, subtemplate))
		return (true);
	candidate->weight |= CANDF_OOB;
	return (false);
}

bool
	mlem_match_template(
		t_mlem_value *value, t_mlem_value *parent, t_mlem_value template)
{
	t_mlem_candidate	best;
	t_mlem_candidate	candidate;
	size_t				i;

	i = early_checks(value, parent, template);
	if ((signed)i >= 0)
		return (i);
	if (template.template_v->structure.type)
		return (match_restrictor(value, template));
	best = (t_mlem_candidate){.parent = parent, .weight = CANDF_UNSET};
	i = 0;
	while (i < template.len)
	{
		if (mlem_match_subtemplate(
				*value, template.template_v->subtemplates[i],
				template.template_v->flags, &candidate)
			&& candidate.weight < best.weight)
		{
			best = candidate;
			if (candidate.weight == 0)
				break ;
		}
		i++;
	}
	printf("%X\n", best.weight);
	return (set_value(value, template, best));
}

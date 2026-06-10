/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reference.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 23:07:38 by rprieur           #+#    #+#             */
/*   Updated: 2026/05/02 23:10:53 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "mlem.h"

t_mlem_value
	mlem_reference_create(t_mlem_string name, t_mlem_value value)
{
	t_mlem_value	reference;

	reference.type = MLEM_TYPE_REFERENCE;
	reference.refv.value = malloc(sizeof(struct s_mlem_reference));
	if (!reference.refv.value)
		return ((t_mlem_value){0});
	reference.refv.is_owner = true;
	reference.refv.value->name = name;
	reference.refv.value->value = value;
	reference.refv.value->ref_count = 1;
	return (reference);
}

t_mlem_value
	mlem_reference(t_mlem_value reference)
{
	t_mlem_value	value;

	value.type = MLEM_TYPE_REFERENCE;
	value.refv.value = reference.refv.value;
	value.refv.is_owner = false;
	reference.refv.value->ref_count++;
	return (value);
}

t_mlem_value
	mlem_dereference(t_mlem_value value)
{
	while (value.type == MLEM_TYPE_REFERENCE)
		value = value.refv.value->value;
	return (value);
}

t_mlem_value
	*mlem_dereference_ptr(t_mlem_value *value)
{
	while (value->type == MLEM_TYPE_REFERENCE)
		value = &value->refv.value->value;
	return (value);
}

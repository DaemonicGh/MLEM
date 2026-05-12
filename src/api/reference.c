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
	mlem_reference(t_mlem_string name, t_mlem_value value)
{
	t_mlem_value	reference;

	reference.type = MLEM_TYPE_REFERENCE;
	reference.reference_v = malloc(sizeof(struct s_mlem_reference));
	if (!reference.reference_v)
		return ((t_mlem_value){0});
	reference.reference_owner = true;
	reference.reference_v->name = name;
	reference.reference_v->value = value;
	reference.reference_v->ref_count = 1;
	return (reference);
}

t_mlem_value
	mlem_dereference(t_mlem_value value)
{
	while (value.type == MLEM_TYPE_REFERENCE)
		value = value.reference_v->value;
	return (value);
}

t_mlem_value
	*mlem_dereference_ptr(t_mlem_value *value)
{
	while (value->type == MLEM_TYPE_REFERENCE)
		value = &value->reference_v->value;
	return (value);
}

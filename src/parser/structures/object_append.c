/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_append.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 13:21:51 by rprieur           #+#    #+#             */
/*   Updated: 2026/05/09 23:00:10 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlem.h"
#include "parser.h"

static t_mlem_pair
	get_values(t_mlem_parser *mlem, t_mlem_value *object,
		t_mlem_token *key, t_mlem_token *value)
{
	t_mlem_pair		pair;

	pair.value = get_string_value(mlem, key, NULL);
	if (!pair.value.type)
		return ((t_mlem_pair){0});
	pair.key = pair.value.string_v;
	if (mlem_object_get(*object, pair.key))
	{
		set_error_t(mlem, key, ERR_DUPLICATED_KEY);
		free(pair.key);
		return ((t_mlem_pair){0});
	}
	pair.value = get_value(mlem, value, pair.key);
	if (!pair.value.type)
	{
		free(pair.key);
		return ((t_mlem_pair){0});
	}
	return (pair);
}

bool
	append_pair(
		t_mlem_parser *mlem, t_mlem_value *object,
		t_mlem_token *key, t_mlem_token *value)
{
	t_mlem_pair	pair;

	pair = get_values(mlem, object, key, value);
	if (!pair.value.type)
		return (false);
	if (mlem_object_append(object, pair.key, pair.value))
		return (true);
	set_error(mlem, ERR_MEMORY);
	free(pair.key);
	mlem_destroy(pair.value);
	return (false);
}

static t_mlem_value
	create_value_reference(t_mlem_parser *mlem,
		t_mlem_value value, t_mlem_value reference, t_mlem_string key)
{
	if (reference.type)
	{
		free(reference.reference_v->name);
		reference.reference_v->name = key;
		reference.reference_v->value = value;
		reference.reference_v->ref_count++;
		reference.reference_owner = true;
		return (reference);
	}
	value = mlem_reference(key, value);
	if (!value.type || !mlem_array_append(&mlem->references, value))
		return ((t_mlem_value){0});
	value.reference_v->ref_count++;
	return (value);
}

bool
	append_pair_reference(
		t_mlem_parser *mlem, t_mlem_value *object,
		t_mlem_token *key, t_mlem_token *value)
{
	t_mlem_value	reference;
	t_mlem_pair		pair;

	reference = get_reference(mlem->references, key);
	if (reference.type && reference.reference_v->value.type)
	{
		set_error_t(mlem, key, ERR_REDEFINING_REFERENCE);
		return (false);
	}
	pair = get_values(mlem, object, key, value);
	if (!pair.value.type)
		return (false);
	pair.value = create_value_reference(mlem, pair.value, reference, pair.key);
	if (pair.value.type && mlem_object_append(object, pair.key, pair.value))
		return (true);
	set_error(mlem, ERR_MEMORY);
	free(pair.key);
	mlem_destroy(pair.value);
	return (false);
}

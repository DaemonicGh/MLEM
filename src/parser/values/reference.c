/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reference.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 01:14:02 by rprieur           #+#    #+#             */
/*   Updated: 2026/05/09 22:59:35 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlem.h"
#include "parser.h"

t_mlem_value
	get_deep_reference(
		const t_mlem_value references, t_mlem_token *token)
{
	t_mlem_value	ret;
	size_t			i;

	i = 0;
	ret = (t_mlem_value){0};
	if (references.type == MLEM_TYPE_ARRAY)
	{
		while (i < references.arrayv.len && !ret.type)
			ret = get_deep_reference(references.arrayv.value[i++], token);
	}
	else if (references.type == MLEM_TYPE_OBJECT)
	{
		while (i < references.objectv.len && !ret.type)
		{
			if (references.objectv.value[i].value.type == MLEM_TYPE_REFERENCE
				&& references.objectv.value[i].value.refv.is_owner
				&& str_eq_tkn_case(references.objectv.value[i].key, token))
				return (references.objectv.value[i].value);
			ret = get_deep_reference(
					references.objectv.value[i++].value, token);
		}
	}
	return (ret);
}

t_mlem_value
	get_reference(const t_mlem_value references, t_mlem_token *token)
{
	size_t			i;

	i = 0;
	while (i < references.arrayv.len)
	{
		if (str_eq_tkn_case(
				references.arrayv.value[i].refv.value->name, token))
			return (references.arrayv.value[i]);
		i++;
	}
	return ((t_mlem_value){0});
}

bool
	create_reference(t_mlem_parser *mlem,
		t_mlem_token *token, t_mlem_string key, t_mlem_value *reference)
{
	t_mlem_value	value;

	value = get_string_value(mlem, token, key);
	if (!value.type)
		return (false);
	*reference = mlem_reference_create(value.strv.value, (t_mlem_value){0});
	if (!reference->type
		|| !mlem_array_append(&mlem->references, *reference))
	{
		set_error(mlem, ERR_MEMORY);
		mlem_destroy(*reference);
		return (false);
	}
	return (true);
}

t_mlem_value
	get_reference_value(
		t_mlem_parser *mlem, t_mlem_token *token, t_mlem_string key)
{
	t_mlem_value	reference;

	reference = get_deep_reference(mlem->outer_references, token);
	if (!reference.type)
		reference = get_reference(mlem->references, token);
	if (!reference.type && !create_reference(mlem, token, key, &reference))
		return ((t_mlem_value){0});
	reference.refv.is_owner = false;
	reference.refv.value->ref_count++;
	return (reference);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 13:59:06 by rprieur           #+#    #+#             */
/*   Updated: 2026/05/07 03:26:49 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static bool
	get_object_token(
		t_mlem_parser *mlem, t_mlem_token *key, t_mlem_token *value)
{
	t_mlem_token	assign;

	if (!expect_next_token(mlem, key, TKG_OBJECT_KEY, ERR_UNEXPECTED_TOKEN))
		return (false);
	if (key->type & TKG_CLOSE)
		return (true);
	if (!expect_next_token(mlem, &assign, TKN_ASSIGN, ERR_EXPECTED_ASSIGN))
		return (false);
	if (!expect_next_token(mlem, value, TKG_OBJECT_VALUE, ERR_EXPECTED_VALUE))
		return (false);
	return (true);
}

static bool
	parse_object(t_mlem_parser *mlem, t_mlem_token *trigger,
		t_mlem_value *object)
{
	t_mlem_token	key;
	t_mlem_token	value;

	while (true)
	{
		if (!get_object_token(mlem, &key, &value))
			return (false);
		if (key.type & TKG_CLOSE)
			return (handle_structure_close(mlem, &key, trigger));
		if (key.type & TKN_REFERENCE)
		{
			if (!append_pair_reference(mlem, object, &key, &value))
				return (false);
		}
		else if (!append_pair(mlem, object, &key, &value))
			return (false);
	}
}

t_mlem_value
	get_object(t_mlem_parser *mlem, t_mlem_token *trigger, t_mlem_string key)
{
	t_mlem_value	object;

	(void)key;
	object = mlem_object_empty(STRUCTURE_BASE_CAPACITY);
	if (!object.type)
	{
		set_error(mlem, ERR_MEMORY);
		return ((t_mlem_value){0});
	}
	if (!parse_object(mlem, trigger, &object))
	{
		mlem_destroy(object);
		return ((t_mlem_value){0});
	}
	mlem_object_resize(&object, object.object_len + 1);
	return (object);
}

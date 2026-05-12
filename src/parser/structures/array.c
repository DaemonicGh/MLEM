/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 13:59:06 by rprieur           #+#    #+#             */
/*   Updated: 2026/05/07 22:34:40 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static bool
	get_array_token(t_mlem_parser *mlem, t_mlem_token *token)
{
	return (expect_next_token(
			mlem, token, TKG_ARRAY_VALUE, ERR_UNEXPECTED_TOKEN));
}

static bool
	append_value(t_mlem_parser *mlem,
		t_mlem_value *array, t_mlem_token *token)
{
	t_mlem_value	value;

	value = get_value(mlem, token, NULL);
	if (!value.type)
		return (false);
	if (mlem_array_append(array, value))
		return (true);
	mlem_destroy(value);
	set_error(mlem, ERR_MEMORY);
	return (false);
}

static bool
	parse_array(
		t_mlem_parser *mlem, t_mlem_token *trigger, t_mlem_value *array)
{
	t_mlem_token	token;

	while (true)
	{
		if (!get_array_token(mlem, &token))
			return (false);
		if (token.type & TKG_CLOSE)
			return (handle_structure_close(mlem, &token, trigger));
		if (!append_value(mlem, array, &token))
			return (false);
	}
}

t_mlem_value
	get_array(t_mlem_parser *mlem, t_mlem_token *trigger, t_mlem_string key)
{
	t_mlem_value	array;

	(void)key;
	array = mlem_array_empty(STRUCTURE_BASE_CAPACITY);
	if (!array.type)
	{
		set_error(mlem, ERR_MEMORY);
		return ((t_mlem_value){0});
	}
	if (!parse_array(mlem, trigger, &array))
	{
		mlem_destroy(array);
		return ((t_mlem_value){0});
	}
	mlem_array_resize(&array, array.array_len + 1);
	return (array);
}

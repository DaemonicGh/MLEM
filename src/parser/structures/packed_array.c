/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   packed_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 13:59:06 by rprieur           #+#    #+#             */
/*   Updated: 2026/05/07 22:34:40 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include ".mlem_values.h"
#include "data.h"
#include "mlem.h"
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
	if (!mlem_tweak(&value, array->packedv.element_type))
	{
		if (value.type == MLEM_TYPE_FLOAT
			&& array->packedv.element_type == MLEM_TYPE_INT)
			set_error_t(mlem, token, ERR_INVALID_PACKED_TYPE_INT_FLOAT);
		else
			set_error_t(mlem, token, ERR_INVALID_PACKED_TYPE);
	}
	else if (!mlem_packed_array_append(array, value))
		set_error(mlem, ERR_MEMORY);
	else
		return (true);
	mlem_destroy(value);
	return (false);
}

static bool
	parse_packed_array(
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

static t_mlem_value	get_packed_array_first(
	t_mlem_parser *mlem, t_mlem_token *trigger)
{
	t_mlem_token	token;
	t_mlem_value	value;

	if (!get_array_token(mlem, &token))
		return ((t_mlem_value){0});
	if (token.type & TKG_CLOSE)
	{
		if (handle_structure_close(mlem, &token, trigger))
			set_error_p(mlem, trigger->true_start, mlem->pos,
				ERR_EMPTY_PACKED_ARRAY);
		return ((t_mlem_value){0});
	}
	value = get_value(mlem, &token, NULL);
	if (!value.type)
		return ((t_mlem_value){0});
	if (!is_valid_packed_type(value.type))
	{
		mlem_destroy(value);
		set_error_p(mlem, token.true_start, mlem->pos,
			ERR_INVALID_PACKED_TYPE_DEFINITION);
		return ((t_mlem_value){0});
	}
	return (value);
}

t_mlem_value
	get_packed_array(
		t_mlem_parser *mlem, t_mlem_token *trigger, t_mlem_string key)
{
	t_mlem_value	array;
	t_mlem_value	value;

	(void)key;
	value = get_packed_array_first(mlem, trigger);
	if (!value.type)
		return ((t_mlem_value){0});
	array = mlem_packed_array_empty(value.type, STRUCTURE_BASE_CAPACITY);
	if (!array.type || !mlem_packed_array_append(&array, value))
	{
		set_error(mlem, ERR_MEMORY);
		mlem_destroy(array);
		mlem_destroy(value);
		return ((t_mlem_value){0});
	}
	if (!parse_packed_array(mlem, trigger, &array))
	{
		mlem_destroy(array);
		return ((t_mlem_value){0});
	}
	mlem_packed_array_resize(&array, array.arrayv.len + 1);
	return (array);
}

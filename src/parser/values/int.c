/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 11:45:42 by rprieur           #+#    #+#             */
/*   Updated: 2026/05/08 02:43:28 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

#include "parser.h"

static bool
	get_int_value_body_end(t_mlem_parser *mlem,
		t_mlem_token *token, t_mlem_value *value, bool valid)
{
	if (!valid)
	{
		if (valid & 1)
			set_error_t(mlem, token, ERR_EMPTY_NUMBER);
		else if (value->int_base == 10)
			set_error_t(mlem, token, ERR_INVALID_NUMBER);
		else
			set_error_t(mlem, token, ERR_INVALID_BASE_NUMBER);
		return (false);
	}
	if (value->__dummy_32)
	{
		value->__dummy_32 = 0;
		if (value->int_v == LONG_MIN)
		{
			set_error_t(mlem, token, ERR_NUMBER_OUT_OF_RANGE);
			return (false);
		}
		value->int_v = -value->int_v;
	}
	return (true);
}

bool
	get_int_value_body(t_mlem_parser *mlem,
		t_mlem_token *token, size_t i, t_mlem_value *value)
{
	t_mlem_int		nval;
	bool			valid;

	valid = false;
	while (i < token->len)
	{
		nval = g_mlem_data.char_data.number[(int)token->start.content[i]];
		if (nval >= 0 && nval < value->int_base)
		{
			value->int_v = value->int_v * value->int_base - nval;
			if (value->int_v > 0)
			{
				set_error_t(mlem, token, ERR_NUMBER_OUT_OF_RANGE);
				return (false);
			}
			valid = true;
		}
		else if (token->start.content[i] != '_')
			break ;
		i++;
	}
	return (get_int_value_body_end(
			mlem, token, value, valid << 1 | (i == token->len)));
}

t_mlem_value
	get_int_value(t_mlem_parser *mlem, t_mlem_token *token)
{
	t_mlem_value	value;
	size_t			i;

	value = (t_mlem_value){.type = MLEM_TYPE_INT};
	i = 0;
	value.__dummy_32 = (get_sign(token, &i) > 0);
	value.int_base = get_base(token, &i);
	if (value.int_base == -1)
	{
		set_error_t(mlem, token, ERR_INVALID_BASE_PREFIX);
		return ((t_mlem_value){0});
	}
	if (get_int_value_body(mlem, token, i, &value))
		return (value);
	return ((t_mlem_value){0});
}

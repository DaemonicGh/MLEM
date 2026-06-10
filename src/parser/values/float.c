/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 11:46:19 by rprieur           #+#    #+#             */
/*   Updated: 2026/05/09 04:43:08 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

#include "parser.h"

static t_mlem_error
	handle_integer(t_mlem_parser *mlem,
		t_mlem_token *token, size_t *i, t_mlem_value *value)
{
	bool			valid;

	valid = false;
	while (*i < token->len)
	{
		if (mlem_isdigit(token->start.content[*i]))
		{
			value->floatv.value = value->floatv.value * 10
				+ (token->start.content[*i] - '0') * value->floatv.exponent;
			if (value->floatv.value != (long)value->floatv.value)
			{
				set_error_t(mlem, token, ERR_NUMBER_OUT_OF_RANGE);
				break ;
			}
			valid = true;
		}
		else if (token->start.content[*i] != '_')
			break ;
		(*i)++;
	}
	return (valid);
}

static bool
	handle_decimal(t_mlem_token *token, size_t *i, t_mlem_value *value)
{
	t_mlem_float	dec;
	bool			valid;

	(*i)++;
	dec = value->floatv.exponent * 0.1;
	valid = false;
	while (*i < token->len)
	{
		if (mlem_isdigit(token->start.content[*i]))
		{
			value->floatv.value += (token->start.content[*i] - '0') * dec;
			dec /= 10;
			valid = true;
		}
		else if (token->start.content[*i] != '_')
			break ;
		(*i)++;
	}
	return (valid);
}

static bool
	apply_float_exponent(t_mlem_parser *mlem,
		t_mlem_token *token, t_mlem_value *value)
{
	t_mlem_int	exp;

	exp = value->floatv.exponent;
	while (exp > 0)
	{
		value->floatv.value *= 10;
		if (value->floatv.value == INFINITY || value->floatv.value == INFINITY)
		{
			set_error_t(mlem, token, ERR_NUMBER_TO_INFINITY);
			return (false);
		}
		exp--;
	}
	while (exp < 0)
	{
		value->floatv.value /= 10;
		exp++;
	}
	return (true);
}

static bool
	handle_float_exponent(t_mlem_parser *mlem,
		t_mlem_token *token, size_t *i, t_mlem_value *value)
{
	int			sign;
	bool		valid;

	(*i)++;
	sign = get_sign(token, i);
	valid = false;
	while (*i < token->len)
	{
		if (mlem_isdigit(token->start.content[*i]))
		{
			value->floatv.exponent *= 10;
			value->floatv.exponent += token->start.content[*i] - '0';
			valid = true;
		}
		else if (token->start.content[*i] != '_')
			break ;
		(*i)++;
	}
	if (valid)
	{
		value->floatv.exponent *= sign;
		return (apply_float_exponent(mlem, token, value));
	}
	set_error_t(mlem, token, ERR_EMPTY_EXPONENT);
	return (false);
}

t_mlem_value
	get_float_value(t_mlem_parser *mlem, t_mlem_token *token)
{
	t_mlem_value	value;
	size_t			i;
	bool			valid;

	value = (t_mlem_value){.floatv = {.type = MLEM_TYPE_FLOAT}};
	i = 0;
	value.floatv.exponent = get_sign(token, &i);
	valid = handle_integer(mlem, token, &i, &value);
	if (mlem->error)
		return ((t_mlem_value){0});
	if (token->start.content[i] == '.'
		&& !handle_decimal(token, &i, &value) && !valid)
	{
		set_error_t(mlem, token, ERR_EMPTY_NUMBER);
		return ((t_mlem_value){0});
	}
	value.floatv.exponent = 0;
	if (mlem_toupper(token->start.content[i]) == 'E'
		&& !handle_float_exponent(mlem, token, &i, &value))
		return ((t_mlem_value){0});
	if (i == token->len)
		return (value);
	set_error_t(mlem, token, ERR_INVALID_NUMBER);
	return ((t_mlem_value){0});
}

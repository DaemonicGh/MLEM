/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 12:44:41 by rprieur           #+#    #+#             */
/*   Updated: 2026/05/09 22:58:08 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "parser.h"

static bool
	try_word_constant(t_mlem_token *token, t_mlem_value *value)
{
	t_mlem_constant	*constants;
	size_t			i;

	i = 0;
	if ((int)token->start.content[0] < 0)
		return (false);
	constants = g_mlem_data.constants[
		g_mlem_data.char_data.constants[(int)token->start.content[0]]];
	while (constants[i].name[0])
	{
		if (str_eq_tkn_case((char *)constants[i].name, token))
		{
			*value = constants[i].value;
			return (true);
		}
		i++;
	}
	return (false);
}

t_mlem_value
	get_word_value(
		t_mlem_parser *mlem, t_mlem_token *token, t_mlem_string key)
{
	t_mlem_value	value;

	if (try_word_constant(token, &value))
		return (value);
	return (get_string_value(mlem, token, key));
}

static bool
	is_float(t_mlem_token *token)
{
	size_t	i;

	i = 0;
	if (token->start.content[i] == '+'
		|| token->start.content[i] == '-')
		i++;
	if (token->start.content[i] == '0')
	{
		if (g_mlem_data.char_data.base[
				(int)token->start.content[i + 1]] != -1)
			return (false);
	}
	while (i < token->len)
	{
		if (token->start.content[i] == '.'
			|| token->start.content[i] == 'e'
			|| token->start.content[i] == 'E')
			return (true);
		i++;
	}
	return (false);
}

t_mlem_value
	get_number_value(
		t_mlem_parser *mlem, t_mlem_token *token, t_mlem_string key)
{
	t_mlem_value	value;

	(void)key;
	if (try_word_constant(token, &value))
		return (value);
	if (is_float(token))
		return (get_float_value(mlem, token));
	else
		return (get_int_value(mlem, token));
}

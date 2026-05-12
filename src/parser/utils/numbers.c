/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numbers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 12:05:14 by rprieur           #+#    #+#             */
/*   Updated: 2026/05/09 04:34:19 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int
	get_sign(t_mlem_token *token, size_t *i)
{
	if (token->start.content[*i] == '-')
	{
		(*i)++;
		return (-1);
	}
	else if (token->start.content[*i] == '+')
		(*i)++;
	return (1);
}

int
	get_base(t_mlem_token *token, size_t *i)
{
	if (token->start.content[*i] != '0'
		|| *i + 1 >= token->len
		|| mlem_isdigit(token->start.content[*i + 1])
		|| token->start.content[*i + 1] == '_')
		return (10);
	(*i)++;
	return (g_mlem_data.char_data.base[(int)token->start.content[(*i)++]]);
}

bool	mlem_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (true);
	return (false);
}

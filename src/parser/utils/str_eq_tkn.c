/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_eq_tkn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 04:45:20 by rprieur           #+#    #+#             */
/*   Updated: 2026/05/10 00:55:21 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	n_transform(
	const char *str, char *result, size_t char_count, int8_t base)
{
	size_t	i;
	int8_t	n;

	n = g_mlem_data.char_data.number[(int)str[1]];
	if (n < 0 || n >= base)
		return (0);
	result[0] = n;
	i = 2;
	while (i <= char_count)
	{
		n = g_mlem_data.char_data.number[(int)str[i]];
		if (n < 0 || n >= base)
			break ;
		result[0] = (result[0] << 4) | n;
		i++;
	}
	return (i);
}

int
	transform(t_mlem_string string, t_mlem_string dest)
{
	if (string[0] == 'x')
		return (n_transform(string, dest, 2, 16));
	dest[0] = g_mlem_data.char_data.transform[(int)string[0]];
	if (dest[0] != ' ')
		return (1);
	dest[0] = string[0];
	return (0);
}

bool	str_eq_tkn_case(t_mlem_string string, t_mlem_token *token)
{
	char	transformed;
	size_t	i;
	size_t	j;
	int		ret;

	i = 0;
	j = 0;
	while (string[i] && j < token->len)
	{
		if (token->start.content[j] == '\\'
			&& token->trigger->data & MLEM_STR_ESCAPE)
		{
			ret = transform(&token->start.content[++j], &transformed);
			if (!ret && !(token->trigger->data & MLEM_STR_LENIENT_ESCAPE))
				return (false);
			j++;
			j += ret - 1;
		}
		else
			transformed = token->start.content[j++];
		if (mlem_toupper(string[i++]) != mlem_toupper(transformed))
			return (false);
	}
	return (!string[i] && j == token->len);
}

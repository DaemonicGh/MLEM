/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 12:17:52 by rprieur           #+#    #+#             */
/*   Updated: 2026/05/09 23:49:16 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlem.h"
#include "parser.h"

static bool
	handle_transform(
		t_mlem_token *token, t_mlem_value *string, size_t *i, size_t *j)
{
	char	transformed;
	int		ret;

	ret = transform(&token->start.content[++(*i)], &transformed);
	if (ret)
	{
		string->string_v[(*j)++] = transformed;
		*i += ret;
	}
	else if (string->string_flavor & MLEM_STR_LENIENT_ESCAPE)
		string->string_v[(*j)++] = token->start.content[(*i)++];
	else
		return (false);
	return (true);
}

static bool
	set_string(t_mlem_token *token, t_mlem_value *string)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < token->len)
	{
		if (token->start.content[i] == '\\'
			&& string->string_flavor & MLEM_STR_ESCAPE)
		{
			if (!handle_transform(token, string, &i, &j))
				return (false);
		}
		else
			string->string_v[j++] = token->start.content[i++];
	}
	string->string_v[j] = 0;
	string->string_len = j;
	return (true);
}

t_mlem_value
	get_string_value(
		t_mlem_parser *mlem, t_mlem_token *token, t_mlem_string key)
{
	t_mlem_value	value;

	(void)key;
	value = (t_mlem_value){.type = MLEM_TYPE_STRING};
	value.string_flavor = token->trigger->data;
	value.string_v = malloc(token->len + 1);
	if (!value.string_v)
	{
		set_error(mlem, ERR_MEMORY);
		return ((t_mlem_value){0});
	}
	if (!set_string(token, &value))
	{
		set_error_t(mlem, token, ERR_INVALID_BACKSLASH);
		free(value.string_v);
		return ((t_mlem_value){0});
	}
	if (token->len - value.string_len > 255)
		value.string_extra_capacity = 255;
	else
		value.string_extra_capacity = token->len - value.string_len;
	return (value);
}

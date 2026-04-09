/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkstrdup_bs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 13:59:06 by rprieur           #+#    #+#             */
/*   Updated: 2026/04/02 14:00:57 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "context.h"
#include "errors.h"
#include "tokens.h"
#include "utils.h"
#include <stdlib.h>

static char
	*alloc(t_mlem_token *token)
{
	char	*str;

	str = malloc(token->len + 1);
	if (!str)
	{
		set_error(ERR_MEMORY);
		return (NULL);
	}
	return (str);
}

static bool	transform(t_mlem_token *token, char *str)
{
	size_t	len;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < token->len)
	{
		if (token->val[i] == '\\')
		{
			str[j] = 0;
			i++;
			len = set_transformed_bs_sequence(token->val + i, str + j);
			if (len == (size_t) - 1)
				return (false);
			i += len;
			while (str[j])
				j++;
		}
		else
			str[j++] = token->val[i++];
	}
	str[j] = 0;
	return (true);
}

char
	*tkstrndup_bs(t_mlem_context *mlem, t_mlem_token *token)
{
	char	*str;

	str = alloc(token);
	if (!str)
		return (NULL);
	if (!transform(token, str))
	{
		set_error_t(mlem, token, ERR_INVALID_BACKSLASH);
		free(str);
		return (NULL);
	}
	return (str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bs_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 13:59:06 by rprieur           #+#    #+#             */
/*   Updated: 2026/04/02 14:01:32 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <string.h>

#include "tokens.h"
#include "utils.h"

static size_t	x_bs(const char *str, char *result)
{
	size_t	n1;
	size_t	n2;

	n1 = strnfind(g_number_values, toupper(str[1]), 15);
	if (n1 == (size_t) -1)
		return (-1);
	n2 = strnfind(g_number_values, toupper(str[2]), 15);
	if (n2 == (size_t) -1)
		return (-1);
	if (result)
	{
		result[0] = (n1 << 4) | n2;
		result[1] = 0;
	}
	return (3);
}

static size_t	x_transform(const char *str, char *result)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (g_backslash_transforms[i][0] &&
		!streq(str, g_backslash_transforms[i][0]))
		i++;
	if (!g_backslash_transforms[i][0])
		return (-1);
	if (result)
	{
		while (g_backslash_transforms[i][1][j])
		{
			result[j] = g_backslash_transforms[i][1][j];
			j++;
		}
		result[j] = 0;
	}
	return (strlen(g_backslash_transforms[i][1]));
}

size_t
	set_transformed_bs_sequence(const char *str, char *result)
{
	if (str[0] == 'x')
		return (x_bs(str, result));
	if (str[0] == '0')
	{
		result[0] = 0;
		return (1);
	}
	return (x_transform(str, result));
}

const char *
	skip_potential_backslash(const char *s)
{
	if (*s == '\\' && *(s + 1))
		return (++s);
	return (s);
}

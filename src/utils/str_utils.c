/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 14:37:15 by rprieur           #+#    #+#             */
/*   Updated: 2026/04/09 14:37:15 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

#include "utils.h"

size_t	mlem_strlen(const char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*mlem_strchr(const char *str, int c)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return ((char *)str + i);
		i++;
	}
	if (c == 0)
		return ((char *)str + i);
	return (NULL);
}

int	mlem_strncmp(const char *str1, const char *str2, size_t size)
{
	size_t	i;

	i = 0;
	if (!size)
		return (0);
	while (str1[i] && str1[i] == str2[i] && i < size - 1)
		i++;
	return (str1[i] - str2[i]);
}

int	mlem_strncasecmp(const char *str1, const char *str2, size_t size)
{
	size_t	i;

	i = 0;
	if (!size)
		return (0);
	while (str1[i] && mlem_toupper(str1[i]) == mlem_toupper(str2[i])
		&& i < size - 1)
		i++;
	return (str1[i] - str2[i]);
}

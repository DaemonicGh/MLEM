/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 14:37:15 by rprieur           #+#    #+#             */
/*   Updated: 2026/05/09 23:09:20 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	mlem_toupper(char c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}

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

char	*mlem_strnchrset(const char *str, const char *set, size_t n)
{
	size_t	i;
	size_t	j;

	if (!str || !set)
		return (NULL);
	i = 0;
	while (str[i] && i < n)
	{
		j = 0;
		while (set[j])
		{
			if (str[i] == set[j])
				return ((char *)(str + i));
			j++;
		}
		i++;
	}
	return (NULL);
}

char	*mlem_strdup(const char *str)
{
	char	*new;
	size_t	len;

	if (!str)
		return (NULL);
	len = mlem_strlen(str);
	new = malloc(len + 1);
	if (!new)
		return (NULL);
	new[len] = 0;
	while (len--)
		new[len] = str[len];
	return (new);
}

size_t
	strctn(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	if (s2[i])
		return (0);
	return (i);
}

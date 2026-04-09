/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   streq.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 13:59:06 by rprieur           #+#    #+#             */
/*   Updated: 2026/04/02 14:01:25 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

size_t
	streq(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	if (s2[i])
		return (0);
	return (i);
}

size_t
	strneq(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i] && n--)
		i++;
	if (s2[i])
		return (0);
	return (i);
}

size_t
	streq_list(const char *s, const char **sa)
{
	size_t	i;

	i = 0;
	while (sa[i])
	{
		if (streq(s, sa[i]))
			return (i);
		i++;
	}
	return (-1);
}

size_t
	strneq_list(const char *s, const char **sa, size_t n)
{
	size_t	i;

	i = 0;
	while (sa[i])
	{
		if (strneq(s, sa[i], n))
			return (i);
		i++;
	}
	return (-1);
}

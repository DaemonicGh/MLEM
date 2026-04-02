/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strchr_bs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 13:59:06 by rprieur           #+#    #+#             */
/*   Updated: 2026/04/02 14:01:29 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

const char*
	strchr_bs(const char *s, char c)
{
	while (*s && *s != c)
	{
		s = skip_potential_backslash(s);
		s++;
	}
	if (*s == c)
		return (s);
	return (NULL);
}

const char*
	strstr_bs(const char *s1, const char *s2)
{
	s1 = strchr_bs(s1, *s2);
	while (s1)
	{
		if (streq(s1, s2))
			return (s1);
		s1 = strchr_bs(++s1, *s2);
	}
	return (NULL);
}

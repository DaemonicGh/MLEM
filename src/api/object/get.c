/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 21:07:18 by rprieur           #+#    #+#             */
/*   Updated: 2026/05/09 04:25:47 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlem.h"

static bool
	keycmp(const t_mlem_string str1, const t_mlem_string str2)
{
	uint32_t	i;

	i = 0;
	while (str1[i] && str1[i] == str2[i])
		i++;
	return (str1[i] == str2[i]);
}

t_mlem_value
	*mlem_object_get(t_mlem_value object, t_mlem_string key)
{
	uint32_t	i;

	i = 0;
	object = mlem_dereference(object);
	while (i < object.object_len)
	{
		if (keycmp(object.object_v[i].key, key))
			return (&object.object_v[i].value);
		i++;
	}
	return (NULL);
}

t_mlem_string
	mlem_object_get_key(t_mlem_value object, t_mlem_value value)
{
	uint32_t	i;

	i = 0;
	object = mlem_dereference(object);
	while (i < object.object_len)
	{
		if (mlem_equal(object.object_v[i].value, value))
			return (object.object_v[i].key);
		i++;
	}
	return (NULL);
}

int64_t
	mlem_object_key_index(t_mlem_value object, t_mlem_string key)
{
	int64_t	i;

	i = 0;
	object = mlem_dereference(object);
	while (i < object.object_len)
	{
		if (keycmp(object.object_v[i].key, key))
			return (i);
		i++;
	}
	return (-1);
}

int64_t
	mlem_object_value_index(t_mlem_value object, t_mlem_value value)
{
	int64_t	i;

	i = 0;
	object = mlem_dereference(object);
	while (i < object.object_len)
	{
		if (mlem_equal(object.object_v[i].value, value))
			return (i);
		i++;
	}
	return (-1);
}

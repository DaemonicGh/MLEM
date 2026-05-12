/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 21:44:40 by rprieur           #+#    #+#             */
/*   Updated: 2026/05/04 18:19:58 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlem.h"

t_mlem_value
	*mlem_array_get(t_mlem_value array, uint32_t index)
{
	array = mlem_dereference(array);
	if (index >= array.array_len)
		return (NULL);
	return (&array.array_v[index]);
}

int64_t
	mlem_array_index(t_mlem_value array, t_mlem_value value)
{
	int64_t	i;

	i = 0;
	array = mlem_dereference(array);
	while (i < array.array_len)
	{
		if (mlem_equal(array.array_v[i], value))
			return (i);
		i++;
	}
	return (-1);
}

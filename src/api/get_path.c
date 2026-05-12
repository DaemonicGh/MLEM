/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 16:28:59 by rprieur           #+#    #+#             */
/*   Updated: 2026/05/04 18:22:41 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlem.h"

t_mlem_value
	*mlem_get_from_path(t_mlem_value value, t_mlem_value path)
{
	t_mlem_value	*current;
	size_t			i;

	i = 0;
	current = &value;
	if (path.array_len == 0 || !current)
		return (NULL);
	while (i < path.array_len && current)
	{
		if (path.array_v[i].type == MLEM_TYPE_INT
			&& current->type == MLEM_TYPE_ARRAY)
			current = mlem_array_get(*current, path.array_v[i].int_v);
		else if (path.array_v[i].type == MLEM_TYPE_STRING
			&& current->type == MLEM_TYPE_OBJECT)
			current = mlem_object_get(*current, path.array_v[i].string_v);
		else
			return (NULL);
		i++;
	}
	return (current);
}

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
	if (path.arrayv.len == 0 || !current)
		return (NULL);
	while (i < path.arrayv.len && current)
	{
		if (path.arrayv.value[i].type == MLEM_TYPE_INT
			&& current->type == MLEM_TYPE_ARRAY)
			current = mlem_array_get(
					*current, path.arrayv.value[i].intv.value);
		else if (path.arrayv.value[i].type == MLEM_TYPE_STRING
			&& current->type == MLEM_TYPE_OBJECT)
			current = mlem_object_get(
					*current, path.arrayv.value[i].strv.value);
		else
			return (NULL);
		i++;
	}
	return (current);
}

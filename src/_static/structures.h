/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 13:59:06 by rprieur           #+#    #+#             */
/*   Updated: 2026/04/02 14:00:37 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "mlem.h"

#define DS_BASE_CAPACITY	4
#define DS_GROW_RATIO		2.0
#define DS_CROP_THRESHOLD	16

#define DA_VALUE_SIZE		sizeof(t_mlem_value)
#define DO_VALUE_SIZE		sizeof(t_mlem_pair)

typedef struct s_mlem_array
{
	t_mlem_value	*data;
	size_t			len;
	size_t			capacity;
	size_t			span;
}	t_mlem_array;

typedef struct s_mlem_object
{
	t_mlem_pair	*data;
	size_t		len;
	size_t		capacity;
	size_t		span;
}	t_mlem_object;

typedef union s_mlem_structure
{
	t_mlem_array	array;
	t_mlem_object	object;
	struct s_mlem_void_structure
	{
		void		*data;
		size_t		len;
		size_t		capacity;
		size_t		span;
	};
}	t_mlem_structure;

t_mlem_structure
ds_new(size_t ele_size);

bool
ds_resize(t_mlem_structure *ds, size_t new_capacity);

t_mlem_array
da_new(void);

bool
da_append(t_mlem_array *array, t_mlem_value ele);

void
da_destroy(t_mlem_array *array, bool free_strings);

t_mlem_object
do_new(void);

bool
do_append(t_mlem_object *object, t_mlem_pair ele);

void
do_destroy(t_mlem_object *object, bool free_strings);

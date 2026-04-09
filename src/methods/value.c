/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   value.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 13:59:06 by rprieur           #+#    #+#             */
/*   Updated: 2026/04/02 14:00:37 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "mlem.h"
#include "errors.h"

static void
	print_value_internal(t_mlem_value *val, size_t depth, bool preceded);

static inline bool
	print_recursive_value(t_mlem_value *val, size_t depth)
{
	const int	tab = depth * 2;
	size_t		i;

	i = 0;
	if (val->type == MLEM_TYPE_OBJECT)
	{
		printf("%*s{\n", tab, "");
		while (val->val_object[i].value.type)
		{
			printf("%*s  \x1B[1m\"%s\"\x1B[0;2m = \x1B[0m",
				tab, "", val->val_object[i].key);
			print_value_internal(&val->val_object[i++].value, depth + 1, true);
		}
		printf("%*s}", tab, "");
	}
	else if (val->type == MLEM_TYPE_ARRAY)
	{
		printf("%*s[\n", tab, "");
		while (val->val_array[i].type)
			print_value_internal(&val->val_array[i++], depth + 1, false);
		printf("%*s]", tab, "");
	}
	else
		return (false);
	return (true);
}

static void
	print_value_internal(t_mlem_value *val, size_t depth, bool preceded)
{
	const int	tab = depth * 2 * !preceded;

	if (!print_recursive_value(val, depth))
	{
		if (val->type == MLEM_TYPE_STRING)
			printf("%*s\"%s\"", tab, "", val->val_string);
		else if (val->type == MLEM_TYPE_INT)
			printf("%*s%zi", tab, "", val->val_int);
		else if (val->type == MLEM_TYPE_FLOAT)
			printf("%*s%f", tab, "", val->val_float);
		else if (val->type == MLEM_TYPE_BOOL)
		{
			if (val->val_bool)
				printf("%*strue", tab, "");
			else
				printf("%*sfalse", tab, "");
		}
		else if (val->type == MLEM_TYPE_NULL)
			printf("%*sNull", tab, "");
		else if (val->type == MLEM_TYPE_ERROR)
			printf("%*sError: %s", tab, "", g_error_messages[val->val_int]);
		else
			printf("%*s???", tab, "");
	}
	printf("\n\x1B[0m");
}

void
	mlem_print_value(t_mlem_value *val)
{
	print_value_internal(val, 0, false);
}

void
	mlem_destroy_value(t_mlem_value *val, bool free_strings)
{
	size_t	i;

	i = 0;
	if (val->type == MLEM_TYPE_OBJECT)
	{
		while (val->val_object[i].value.type)
		{
			if (free_strings)
				free(val->val_object[i].key);
			mlem_destroy_value(&val->val_object[i++].value, free_strings);
		}
		free(val->val_object);
	}
	else if (val->type == MLEM_TYPE_ARRAY)
	{
		while (val->val_array[i].type)
			mlem_destroy_value(&val->val_array[i++], free_strings);
		free(val->val_array);
	}
	else if (val->type == MLEM_TYPE_STRING)
	{
		if (free_strings)
			free(val->val_string);
	}
	*val = (t_mlem_value){.val_int = ERR_NONE};
}

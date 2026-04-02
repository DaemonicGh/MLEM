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
#include <string.h>
#include <stdlib.h>

#include "mlem.h"
#include "errors.h"

static void
	print_value_internal(t_mlem_value *val, size_t depth, bool preceded)
{
	char		tab[65];

	if (depth > 32)
		depth = 32;
	memset(tab, ' ', depth * 2);
	tab[depth * 2] = '\0';
	if (!preceded)
		printf("%s", tab);

	switch (val->type)
	{
		case MLEM_TYPE_ARRAY:
			printf("[\n");
			for (size_t i = 0; val->val_array[i].type; i++)
				print_value_internal(&val->val_array[i], depth + 1, false);
			printf("%s]", tab);
			break ;

		case MLEM_TYPE_OBJECT:
			printf("{\n");
			for (size_t i = 0; val->val_object[i].value.type; i++)
			{
				printf("%s  \x1B[1m\"%s\"\x1B[0;2m = \x1B[0m", tab, val->val_object[i].key);
				print_value_internal(&val->val_object[i].value, depth + 1, true);
			}
			printf("%s}", tab);
			break ;

		case MLEM_TYPE_STRING:
			printf("\"%s\"", val->val_string);
			break ;

		case MLEM_TYPE_INT:
			printf("%zi", val->val_int);
			break ;

		case MLEM_TYPE_FLOAT:
			printf("%f", val->val_float);
			break ;

		case MLEM_TYPE_BOOL:
			if (val->val_bool)
				printf("true");
			else
				printf("false");
			break ;

		case MLEM_TYPE_NULL:
			printf("Null");
			break ;

		case MLEM_TYPE_ERROR:
			printf("Error: %s", g_error_messages[val->val_int]);
			break ;

		default:
			printf("???");
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
	switch (val->type) {

		case MLEM_TYPE_ARRAY:
			for (size_t i = 0; val->val_array[i].type; i++)
				mlem_destroy_value(&val->val_array[i], free_strings);
			free(val->val_array);
			break ;

		case MLEM_TYPE_OBJECT:
			for (size_t i = 0; val->val_object[i].value.type; i++)
			{
				if (free_strings)
					free(val->val_object[i].key);
				mlem_destroy_value(&val->val_object[i].value, free_strings);
			}
			free(val->val_object);
			break ;

		case MLEM_TYPE_STRING:
			if (free_strings)
				free(val->val_string);
			break ;

		default: break ;
	}
	*val = MLEM_ERROR_VALUE(ERR_NONE);
}

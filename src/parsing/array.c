/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 13:59:06 by rprieur           #+#    #+#             */
/*   Updated: 2026/04/02 14:00:37 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "mlem.h"
#include "parser.h"
#include "structures.h"
#include "errors.h"
#include "tokens.h"

static bool
	append_value(t_mlem_context *mlem, t_mlem_array *array, t_mlem_token *token)
{
	t_mlem_value	val;

	if (token->type & TKG_WORD)
	{
		val = get_value(mlem, token);
		if (val.type)
		{
			if (da_append(array, val))
				return (true);
			free(val.val_string);
			mlem->error = set_error(ERR_MEMORY);
		}
	}
	else if (token->type & TKG_OPEN)
	{
		val = parse_structure(mlem, token);
		if (!val.type)
			return (false);
		if (da_append(array, val))
			return (true);
		mlem->error = set_error(ERR_MEMORY);
	}
	else
		set_error_t(mlem, token, ERR_UNEXPECTED_TOKEN);
	return (false);
}

static t_mlem_value
	send_array(t_mlem_array *array)
{
	if (array->len + DS_CROP_THRESHOLD < array->capacity)
		ds_resize((t_mlem_structure *)array, array->len);
	return ((t_mlem_value){.type = MLEM_TYPE_ARRAY, .val_array = array->data});
}

static bool
	parse_array_loop(
		t_mlem_context *mlem, t_mlem_token *trigger_token, t_mlem_array *array)
{
	t_mlem_token	token;

	while (true)
	{
		token = get_next_token(mlem);
		if (!token.type)
			return (!mlem->error);
		if (token.type & TKG_CLOSE)
		{
			if (mlem->depth == 0)
				set_error_t(mlem, &token, ERR_UNEXPECTED_TOKEN);
			else if (trigger_token->type & ~(token.type >> 1))
				set_error_t(mlem, &token, ERR_WRONG_STRUCTURE_CLOSE);
			else
				return (true);
			return (false);
		}
		if (!append_value(mlem, array, &token))
			return (false);
	}
}

t_mlem_value
	parse_array(t_mlem_context *mlem, t_mlem_token *trigger_token)
{
	t_mlem_array	array;

	array = da_new();
	if (!array.data)
	{
		mlem->error = set_error(ERR_MEMORY);
		return ((t_mlem_value){.val_int = ERR_MEMORY});
	}
	if (parse_array_loop(mlem, trigger_token, &array))
		return (send_array(&array));
	da_destroy(&array, true);
	return ((t_mlem_value){.val_int = mlem->error});
}

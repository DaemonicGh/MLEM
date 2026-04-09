/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 13:59:06 by rprieur           #+#    #+#             */
/*   Updated: 2026/04/02 14:00:37 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "parser.h"
#include "structures.h"
#include "errors.h"

static t_mlem_value
	send_object(t_mlem_object *object)
{
	if (object->len + DS_CROP_THRESHOLD < object->capacity)
		ds_resize((t_mlem_structure *)object, object->len);
	return ((t_mlem_value){
		.type = MLEM_TYPE_OBJECT,
		.val_object = object->data});
}

static bool
	parse_object_loop(t_mlem_context *mlem, t_mlem_token *trigger_token,
		t_mlem_object *object)
{
	t_mlem_token	key;
	t_mlem_token	value;

	while (true)
	{
		if (!get_key_value_tokens(mlem, &key, &value))
			return (!mlem->error);
		if (key.type & TKG_CLOSE)
		{
			if (mlem->depth == 0)
				set_error_t(mlem, &key, ERR_UNEXPECTED_TOKEN);
			else if (trigger_token->type & ~(key.type >> 1))
				set_error_t(mlem, &key, ERR_WRONG_STRUCTURE_CLOSE);
			else
				return (true);
			return (false);
		}
		if (!append_pair(mlem, object, &key, &value))
			return (false);
	}
}

t_mlem_value
	parse_object(t_mlem_context *mlem, t_mlem_token *trigger_token)
{
	t_mlem_object	object;

	object = do_new();
	if (!object.data)
	{
		mlem->error = set_error(ERR_MEMORY);
		return ((t_mlem_value){.val_int = ERR_MEMORY});
	}
	if (parse_object_loop(mlem, trigger_token, &object))
		return (send_object(&object));
	do_destroy(&object, true);
	return ((t_mlem_value){.val_int = mlem->error});
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 13:21:51 by rprieur           #+#    #+#             */
/*   Updated: 2026/04/09 13:21:51 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "mlem.h"
#include "parser.h"
#include "structures.h"
#include "errors.h"
#include "tokens.h"
#include "utils.h"

static bool
	is_dup_key(t_mlem_token *key, t_mlem_object *object)
{
	size_t	i;

	i = 0;
	while (i < object->len)
	{
		if (mlem_strncmp(object->data[i].key, key->val, key->len) == 0
			&& !object->data[i].key[key->len])
			return (true);
		i++;
	}
	return (false);
}

static bool
	get_valueless_tokens(
		t_mlem_context *mlem, t_mlem_token *key)
{
	*key = get_next_token(mlem);
	if (!key->type)
		return (true);
	if (key->type & ~TKG_OBJECT_KEY)
	{
		set_error_t(mlem, key, ERR_UNEXPECTED_TOKEN);
		key->type = TK_NULL;
		return (true);
	}
	if (key->type & TKG_CLOSE)
		return (true);
	return (false);
}

bool
	get_key_value_tokens(
		t_mlem_context *mlem, t_mlem_token *key, t_mlem_token *value)
{
	t_mlem_token	assign;

	if (get_valueless_tokens(mlem, key))
		return (key->type);
	assign = get_next_token(mlem);
	if (!assign.type && mlem->error)
		return (false);
	if (!assign.type || assign.type & ~TK_ASSIGN)
	{
		set_error_t(mlem, &assign, ERR_EXPECTED_ASSIGN);
		return (false);
	}
	*value = get_next_token(mlem);
	if (!value->type && mlem->error)
	{
		set_error_l(mlem, ERR_EXPECTED_VALUE);
		return (false);
	}
	if (!assign.type && key->type & ~TKG_OBJECT_VALUE)
	{
		set_error_t(mlem, value, ERR_UNEXPECTED_TOKEN);
		return (false);
	}
	return (true);
}

static bool
	append_pair_value(
		t_mlem_context *mlem, t_mlem_object *object,
		t_mlem_pair pair, t_mlem_token *value)
{
	if (value->type & TKG_VALUE)
	{
		pair.value = get_value(mlem, value);
		if (!pair.value.type)
			return (false);
		if (do_append(object, pair))
			return (true);
		if (value->type & TKG_ALLOCD_VALUE)
			free(pair.value.val_string);
		mlem->error = set_error(ERR_MEMORY);
	}
	else if (value->type & TKG_OPEN)
	{
		pair.value = parse_structure(mlem, value);
		if (!pair.value.type)
			return (false);
		if (do_append(object, pair))
			return (true);
		mlem->error = set_error(ERR_MEMORY);
	}
	else
		set_error_t(mlem, value, ERR_UNEXPECTED_TOKEN);
	return (false);
}

bool
	append_pair(
		t_mlem_context *mlem, t_mlem_object *object,
		t_mlem_token *key, t_mlem_token *value)
{
	t_mlem_pair	pair;

	if (key->type & ~TKG_WORD)
	{
		set_error_t(mlem, key, ERR_UNEXPECTED_TOKEN);
		return (false);
	}
	if (is_dup_key(key, object))
	{
		set_error_t(mlem, key, ERR_DUPLICATED_KEY);
		return (false);
	}
	pair.key = tkstrndup_bs(mlem, key);
	if (!pair.key)
		return (false);
	if (!append_pair_value(mlem, object, pair, value))
	{
		free(pair.key);
		return (false);
	}
	return (true);
}

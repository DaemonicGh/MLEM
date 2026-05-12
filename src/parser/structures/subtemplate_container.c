/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subtemplate_container.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 21:30:21 by rprieur           #+#    #+#             */
/*   Updated: 2026/05/09 03:18:29 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static bool
	check_container(t_mlem_parser *mlem,
		t_mlem_token *token, t_mlem_value value, bool origin);

static bool
	check_structure_container(t_mlem_parser *mlem,
		t_mlem_token *token, t_mlem_value value)
{
	size_t	i;

	i = 0;
	if (value.type == MLEM_TYPE_ARRAY)
	{
		while (i < value.array_v->array_len && check_container(mlem, token,
				value.array_v[i], false))
			i++;
		if (i == value.array_v->array_len)
			return (true);
		set_error_p(mlem, token->true_start, mlem->pos,
			ERR_INVALID_SUBTEMPLATE_STRUCTURE);
	}
	else if (value.type == MLEM_TYPE_OBJECT)
	{
		while (i < value.object_len && check_container(mlem, token,
				value.object_v[i].value, false))
			i++;
		if (i == value.object_len)
			return (true);
		set_error_p(mlem, token->true_start, mlem->pos,
			ERR_INVALID_SUBTEMPLATE_STRUCTURE);
	}
	return (false);
}

static bool
	check_container(t_mlem_parser *mlem,
		t_mlem_token *token, t_mlem_value value, bool origin)
{
	if (!(value.type & TYPEG_CONTAINER))
	{
		if (origin)
			set_error_p(mlem, token->true_start, mlem->pos,
				ERR_INVALID_SUBTEMPLATE);
		return (false);
	}
	if (value.type == MLEM_TYPE_TEMPLATE)
		return (true);
	if (value.type == MLEM_TYPE_REFERENCE)
	{
		if (mlem_dereference(value).type == MLEM_TYPE_TEMPLATE)
			return (true);
		set_error_p(mlem, token->true_start, mlem->pos,
			ERR_INVALID_SUBTEMPLATE_REFERENCE);
		return (false);
	}
	return (check_structure_container(mlem, token, value));
}

static int
	get_full_container(t_mlem_parser *mlem, t_mlem_value *template,
		t_mlem_token *token, t_mlem_value value)
{
	if (!check_container(mlem, token, value, true))
	{
		mlem_destroy(value);
		return (false);
	}
	if (mlem_template_append(template, value))
		return (-1);
	set_error(mlem, ERR_MEMORY);
	return (false);
}

int
	get_subtemplate_container(t_mlem_parser *mlem, t_mlem_value *template,
		t_mlem_token *token)
{
	t_mlem_subtemplate	last;
	t_mlem_value		value;

	value = get_value(mlem, token, NULL);
	if (!value.type)
		return (false);
	last = template->template_v->subtemplates[template->template_len - 1];
	if (last.type & TYPEG_CTN_RANGE && !last.array_v
		&& get_subtemplate_data(last, value))
		return (-1);
	return (get_full_container(mlem, template, token, value));
}

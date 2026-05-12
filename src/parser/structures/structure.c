/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 13:59:06 by rprieur           #+#    #+#             */
/*   Updated: 2026/05/07 20:33:04 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_mlem_value_type
	get_unknown_structure_type(t_mlem_parser *mlem)
{
	t_mlem_parser	mlem_tmp;
	t_mlem_token	token;

	mlem_tmp = *mlem;
	if (!expect_next_token(&mlem_tmp, &token,
			TKG_STRUCTURE_VALUE, ERR_UNEXPECTED_TOKEN))
		return (MLEM_TYPE_NONE);
	if (token.type & (TKG_CLOSE | TKG_OPEN))
		return (MLEM_TYPE_ARRAY);
	if (!expect_next_token(&mlem_tmp, &token,
			TKG_STRUCTURE_VALUE | TKN_ASSIGN, ERR_UNEXPECTED_TOKEN))
		return (MLEM_TYPE_NONE);
	if (token.type & TKN_ASSIGN)
		return (MLEM_TYPE_OBJECT);
	return (MLEM_TYPE_ARRAY);
}

static t_mlem_value_type
	get_structure_type(t_mlem_parser *mlem, t_mlem_token *trigger_token)
{
	if (trigger_token->trigger->data == TRG_OPEN_ARRAY)
		return (MLEM_TYPE_ARRAY);
	if (trigger_token->trigger->data == TRG_OPEN_OBJECT)
		return (MLEM_TYPE_OBJECT);
	if (trigger_token->trigger->data == TRG_OPEN_TEMPLATE)
		return (MLEM_TYPE_TEMPLATE);
	if (trigger_token->trigger->data == TRG_OPEN_STRUCTURE)
		return (get_unknown_structure_type(mlem));
	set_error_t(mlem, trigger_token, ERR_UNEXPECTED_TOKEN);
	return (MLEM_TYPE_NONE);
}

t_mlem_value
	get_structure(t_mlem_parser *mlem, t_mlem_token *token, t_mlem_string key)
{
	t_mlem_value		structure;

	mlem->depth++;
	structure.type = get_structure_type(mlem, token);
	if (structure.type == MLEM_TYPE_ARRAY)
		structure = get_array(mlem, token, key);
	else if (structure.type == MLEM_TYPE_OBJECT)
		structure = get_object(mlem, token, key);
	else if (structure.type == MLEM_TYPE_TEMPLATE)
		structure = get_template(mlem, token, key);
	else
		structure = (t_mlem_value){0};
	mlem->depth--;
	return (structure);
}

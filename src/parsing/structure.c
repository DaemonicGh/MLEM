/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 13:59:06 by rprieur           #+#    #+#             */
/*   Updated: 2026/04/02 14:00:37 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "errors.h"
#include "mlem.h"
#include "parser.h"
#include "tokens.h"

t_mlem_value_type
static get_structure_type(t_mlem_context *mlem)
{
	t_mlem_context	t_mlem_sp	= *mlem;
	t_mlem_token		token;

	token = get_next_token(&t_mlem_sp);
	if (!token.type)
		return (MLEM_TYPE_NULL);
	if (token.type & (TKG_CLOSE | TKG_OPEN))
		return (MLEM_TYPE_ARRAY);
	if (token.type & ~TKG_WORD)
	{
		set_error_l(mlem, ERR_UNEXPECTED_TOKEN);
		return (MLEM_TYPE_NULL);
	}

	token = get_next_token(&t_mlem_sp);
	if (!token.type && mlem->error)
		return (MLEM_TYPE_NULL);
	if (token.type & TK_ASSIGN)
		return (MLEM_TYPE_OBJECT);
	return (MLEM_TYPE_ARRAY);
}

t_mlem_value
parse_structure(t_mlem_context *mlem, t_mlem_token *trigger_token)
{
	t_mlem_value		structure = (t_mlem_value){0};

	mlem->depth++;
	if (trigger_token->type & TK_OPEN_UNKNOWN)
	{
		//printf("(\n");
		structure.type = get_structure_type(mlem);
		//printf(")\n");
	}
	if (structure.type == MLEM_TYPE_ARRAY ||
		trigger_token->type & TK_OPEN_ARRAY)
		structure = parse_array(mlem, trigger_token);
	else if (structure.type == MLEM_TYPE_OBJECT ||
		trigger_token->type & TK_OPEN_OBJECT)
		structure = parse_object(mlem, trigger_token);
	else if (mlem->error)
		structure = MLEM_ERROR_VALUE(mlem->error);

	mlem->depth--;
	return (structure);
}

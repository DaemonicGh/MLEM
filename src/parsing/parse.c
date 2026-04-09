/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 13:59:06 by rprieur           #+#    #+#             */
/*   Updated: 2026/04/02 14:00:37 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlem.h"
#include "errors.h"
#include "parser.h"
#include "tokens.h"

t_mlem_value
	mlem_parse(char *content, const t_mlem_value *constants)
{
	t_mlem_context		mlem;
	t_mlem_value		structure;

	if (!content)
	{
		set_error(ERR_NULL_INPUT);
		return ((t_mlem_value){.val_int = ERR_NONE});
	}
	mlem = init_context(content, constants);
	if (mlem.error)
		return ((t_mlem_value){.val_int = mlem.error});
	parse_start(&mlem);
	structure = parse_structure(&mlem, &(t_mlem_token)
		{.type = TK_OPEN_UNKNOWN, .trigger = &g_token_triggers[6]});
	if (!structure.type)
		return ((t_mlem_value){.val_int = mlem.error});
	return (structure);
}

t_mlem_value
	mlem_parse_file(
		const char *filename, char **content, const t_mlem_value *constants)
{
	t_mlem_error	error;

	*content = open_and_read_file(filename, &error);
	if (!*content)
		return ((t_mlem_value){.val_int = error});
	return (mlem_parse(*content, constants));
}

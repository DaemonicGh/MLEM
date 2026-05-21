/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 13:59:06 by rprieur           #+#    #+#             */
/*   Updated: 2026/05/09 03:07:33 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "parser.h"

static bool
	set_content(t_mlem_parser *mlem)
{
	t_mlem_parser	mlem_tmp;

	if (mlem->filename && !set_file_contents(mlem))
		return (false);
	mlem->pos.content = mlem->start;
	mlem_tmp = *mlem;
	if (!mlem->pos.content || get_next_token(&mlem_tmp).type == TKN_EOF)
	{
		set_error(mlem, ERR_EMPTY_FILE);
		return (true);
	}
	return (false);
}

static bool
	set_references(t_mlem_parser *mlem)
{
	if (mlem->outer_references.type & ~(MLEM_TYPE_ARRAY | MLEM_TYPE_OBJECT))
	{
		set_error(mlem, ERR_INVALID_OUTER_REFERENCES);
		return (false);
	}
	mlem->references = mlem_array_empty(STRUCTURE_BASE_CAPACITY);
	if (!mlem->references.type)
	{
		set_error(mlem, ERR_MEMORY);
		return (false);
	}
	return (true);
}

t_mlem_parser
	init_context(const char *filename, char *content,
		const t_mlem_value outer_references)
{
	t_mlem_parser	mlem;

	mlem = (t_mlem_parser){
		.pos = {.line = 1, .column = 1}, .depth = -1,
		.filename = filename, .start = content,
		.outer_references = outer_references,
		.error = ERR_NONE
	};
	if (!set_references(&mlem))
		return (mlem);
	if (!set_content(&mlem))
		return (mlem);
	return (mlem);
}

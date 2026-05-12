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

#include <stdio.h>
#include <stdlib.h>

#include "data.h"
#include "mlem.h"
#include "parser.h"

static size_t	get_file_size(t_mlem_parser *mlem, FILE *file)
{
	size_t	content_size;

	if (!file)
	{
		set_error(mlem, ERR_FILE);
		return (0);
	}
	if (fseek(file, 0, SEEK_END))
	{
		set_error(mlem, ERR_FILE);
		fclose(file);
		return (0);
	}
	content_size = ftell(file);
	if (!content_size || fseek(file, 0, SEEK_SET))
	{
		set_error(mlem, ERR_FILE);
		fclose(file);
		return (0);
	}
	return (content_size);
}

static bool
	set_file_contents(t_mlem_parser *mlem)
{
	FILE	*file;
	size_t	content_size;

	file = fopen(mlem->filename, "r");
	content_size = get_file_size(mlem, file);
	if (!content_size)
		return (false);
	mlem->start = malloc(content_size + 1);
	if (!mlem->start)
	{
		set_error(mlem, ERR_MEMORY);
		fclose(file);
		return (false);
	}
	fread(mlem->start, 1, content_size, file);
	mlem->start[content_size] = '\0';
	fclose(file);
	return (true);
}

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
		set_error(mlem, ERR_EMPTY_INPUT);
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

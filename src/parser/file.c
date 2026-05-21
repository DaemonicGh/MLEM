/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 17:55:57 by rprieur           #+#    #+#             */
/*   Updated: 2026/05/21 17:55:57 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm-generic/errno-base.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "parser.h"

static bool	file_error(t_mlem_parser *mlem, FILE *file)
{
	if (errno == EAGAIN)
	{
		mlem->start = NULL;
		return (true);
	}
	set_error_v(mlem, ERR_FILE, (t_mlem_value){
		.type = MLEM_TYPE_STRING, .string_v = strerror(errno)});
	if (file)
		fclose(file);
	return (false);
}

bool	set_file_contents(t_mlem_parser *mlem)
{
	FILE	*file;
	size_t	content_size;

	file = fopen(mlem->filename, "r");
	if (!file)
		return (file_error(mlem, file));
	if (fseek(file, 0, SEEK_END))
		return (file_error(mlem, file));
	content_size = ftell(file);
	if (!content_size || fseek(file, 0, SEEK_SET))
		return (file_error(mlem, file));
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

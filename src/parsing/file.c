/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 13:59:06 by rprieur           #+#    #+#             */
/*   Updated: 2026/04/02 14:00:37 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "mlem.h"
#include "errors.h"

char*
	open_and_read_file(const char *filename, t_mlem_error *error)
{
	FILE	*file;
	char	*content;
	size_t	content_size;

	file = fopen(filename, "r");
	if (!file)
	{
		*error = set_error(ERR_FILE);
		return (NULL);
	}
	fseek(file, 0, SEEK_END);
	content_size = ftell(file);
	fseek(file, 0, SEEK_SET);
	content = malloc(content_size + 1);
	if (!content)
	{
		*error = set_error(ERR_MEMORY);
		fclose(file);
		return (NULL);
	}
	fread(content, 1, content_size, file);
	content[content_size] = '\0';
	*error = ERR_NONE;
	fclose(file);
	return (content);
}

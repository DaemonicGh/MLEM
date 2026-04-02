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

#include <stdio.h>
#include <strings.h>

#include "mlem.h"
#include "errors.h"
#include "parser.h"

t_mlem_value
t_mlem_parse(char *content, t_mlem_settings settings)
{
	t_mlem_token			start_token = {.type = TK_OPEN_UNKNOWN, .trigger = &g_token_triggers[6]};
	t_mlem_context		mlem;
	t_mlem_value			structure;

	if (!content)
	{
		set_error(ERR_NULL_INPUT);
		return (MLEM_ERROR_VALUE(ERR_NONE));
	}
	mlem = init_context(content, settings);
	parse_start(&mlem);
	printf("Starting parsing\n");
	structure = parse_structure(&mlem, &start_token);
	if (!structure.type)
		return (MLEM_ERROR_VALUE(mlem.error));
	return (structure);
}

t_mlem_value
t_mlem_parse_file(const char *filename, char **content, t_mlem_settings settings)
{
	t_mlem_error error;

	*content = open_and_read_file(filename, &error);
	if (!*content)
		return (MLEM_ERROR_VALUE(error));
	printf("Read File\n");
	return (t_mlem_parse(*content, settings));
}

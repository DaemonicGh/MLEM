/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 13:59:06 by rprieur           #+#    #+#             */
/*   Updated: 2026/05/09 03:29:21 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdio.h>

t_mlem_error
	set_error(t_mlem_parser *mlem, t_mlem_error type)
{
	fputs(ASCII_ERR1 "MLEM" ASCII_ERR3 " - Error", stderr);
	if (mlem->filename)
	{
		fputs(" in " ASCII_ERR2, stderr);
		fputs(mlem->filename, stderr);
	}
	fputs(ASCII_ERR1 "\n", stderr);
	fputs(g_error_messages[type][0], stderr);
	fputc('\n', stderr);
	if (g_error_messages[type][1])
	{
		fputs(ASCII_ERR4, stderr);
		fputs(g_error_messages[type][1], stderr);
		fputc('\n', stderr);
	}
	fputs(ASCII_RESET, stderr);
	mlem->error = type;
	return (type);
}

t_mlem_error
	set_error_v(t_mlem_parser *mlem, t_mlem_error type, t_mlem_value value)
{
	fputs(ASCII_ERR1 "MLEM" ASCII_ERR3 " - Error", stderr);
	if (mlem->filename)
	{
		fputs(" in " ASCII_ERR2, stderr);
		fputs(mlem->filename, stderr);
	}
	fputs(ASCII_ERR1 "\n", stderr);
	fputs(g_error_messages[type][0], stderr);
	fputc('\n', stderr);
	if (value.type)
	{
		fputs(" on" ASCII_ERR3 " :\n", stderr);
		mlem_print(stderr, value);
	}
	else
		fputc('\n', stderr);
	if (g_error_messages[type][1])
	{
		fputs(ASCII_ERR4, stderr);
		fputs(g_error_messages[type][1], stderr);
		fputc('\n', stderr);
	}
	fputs(ASCII_RESET, stderr);
	mlem->error = type;
	return (type);
}

static int
	get_limit(t_mlem_parser *mlem, t_mlem_position pos, int dir)
{
	int		off;
	int		l;
	int		nl;

	off = -(dir < 0);
	l = pos.column - 1;
	nl = 0;
	while (l < 40 && pos.content + off >= mlem->start && pos.content[off])
	{
		if (pos.content[off] == '\n')
		{
			if (nl >= 1)
				return (off);
			nl++;
			l = 0;
		}
		off += dir;
		l++;
	}
	return (off);
}

t_mlem_error
	set_error_p(t_mlem_parser *mlem,
		t_mlem_position start, t_mlem_position end, t_mlem_error type)
{
	int			start_i;
	int			end_i;

	start_i = -get_limit(mlem, start, -1) - 1;
	end_i = get_limit(mlem, end, 1);
	fputs(ASCII_ERR1 "MLEM" ASCII_ERR3 " - Error", stderr);
	if (mlem->filename)
	{
		fputs(" in " ASCII_ERR2, stderr);
		fputs(mlem->filename, stderr);
	}
	fprintf(stderr, ASCII_ERR1 "\n%s" ASCII_ERR3 " at line "
		ASCII_ERR1 "%u" ASCII_ERR3 ":" ASCII_ERR1 "%u\n",
		g_error_messages[type][0], start.line, start.column);
	if (g_error_messages[type][1])
		fprintf(stderr, ASCII_ERR4 "%s\n", g_error_messages[type][1]);
	fprintf(stderr,
		ASCII_TXT1 "╌╶╴─╼╾━━━━━━━━━━━━━━━━━━━━━━━━━━━━╼╾─╶╴╌\n"
		ASCII_TXT2 "%.*s" ASCII_ERR0 "%.*s" ASCII_TXT2 "%.*s\n"
		ASCII_TXT1 "╌╶╴─╼╾━━━━━━━━━━━━━━━━━━━━━━━━━━━━╼╾─╶╴╌\n",
		start_i, start.content - start_i,
		(int)(end.content - start.content),
		start.content, end_i, end.content);
	mlem->error = type;
	return (type);
}

t_mlem_error
	set_error_t(t_mlem_parser *mlem, t_mlem_token *token, t_mlem_error type)
{
	set_error_p(mlem, token->true_start, token->true_end, type);
	token->type = TKN_ERROR;
	return (type);
}

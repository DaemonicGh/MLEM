/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
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
#include "tokens.h"

t_mlem_error
	set_error(t_mlem_error type)
{
	fprintf(stderr, "\x1B[1;31mMLEM: %s\x1B[0m\n", g_error_messages[type]);
	return (type);
}

t_mlem_error
	set_error_l(t_mlem_context *mlem, t_mlem_error type)
{
	fprintf(stderr, "\x1B[1;31mMLEM: %s at line %zi:%zi\x1B[0m\n",
		g_error_messages[type], mlem->line, mlem->column);
	mlem->error = type;
	return (type);
}

t_mlem_error
	set_error_t(t_mlem_context *mlem, t_mlem_token *token, t_mlem_error type)
{
	fprintf(stderr, "\x1B[1;31mMLEM: %s at line %zi:%zi > %.*s\x1B[0m\n",
		g_error_messages[type], mlem->line, mlem->column,
		(int)token->len, token->val);
	mlem->error = type;
	return (type);
}

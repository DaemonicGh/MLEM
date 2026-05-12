/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 00:39:42 by rprieur           #+#    #+#             */
/*   Updated: 2026/05/07 21:46:56 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool
	handle_structure_close(t_mlem_parser *mlem,
		t_mlem_token *token, t_mlem_token *trigger)
{
	if (token->type & TKN_EOF)
		return (true);
	if (trigger->trigger == &g_mlem_data.tokens[token->trigger->data])
		return (true);
	set_error_t(mlem, token, ERR_WRONG_STRUCTURE_CLOSE);
	return (false);
}

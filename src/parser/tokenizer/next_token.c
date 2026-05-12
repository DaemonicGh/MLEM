/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 10:26:11 by rprieur           #+#    #+#             */
/*   Updated: 2026/05/07 23:05:57 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static bool
	token_checks(t_mlem_parser *mlem, t_mlem_token *token)
{
	if (token->type & TKN_UNEXPECTED)
		set_error_t(mlem, token, ERR_UNEXPECTED_TOKEN);
	else if (token->type & TKN_EOF && mlem->depth > 0)
		set_error(mlem, ERR_UNCLOSED_STRUCTURE);
	else if (token->type & TKN_CLOSE && mlem->depth == 0)
		set_error_t(mlem, token, ERR_EXTRA_STRUCTURE_CLOSE);
	else
		return (true);
	return (false);
}

t_mlem_token
	get_next_token(t_mlem_parser *mlem)
{
	t_mlem_token			token;

	token = get_token(mlem);
	while (token.type & TKG_UNSIGNIFICANT)
		token = get_token(mlem);
	if (!token_checks(mlem, &token))
		token.type = TKN_ERROR;
	return (token);
}

bool
	expect_next_token(t_mlem_parser *mlem, t_mlem_token *token,
		uint32_t whitelist, t_mlem_error error)
{
	*token = get_next_token(mlem);
	if (!(token->type & whitelist))
	{
		if (token->type)
			set_error_t(mlem, token, error);
		return (false);
	}
	return (true);
}

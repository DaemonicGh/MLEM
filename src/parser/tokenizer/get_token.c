/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 13:59:06 by rprieur           #+#    #+#             */
/*   Updated: 2026/05/09 23:26:31 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "parser.h"

static t_mlem_token_trigger
	*set_token_start(
		t_mlem_parser *mlem, t_mlem_token *token)
{
	t_mlem_token_trigger	*trigger;

	token->true_start = mlem->pos;
	if (token->trigger->type == TKN_BACKSLASH)
	{
		move_forward(mlem, token->trigger->len - 1);
		token->start = mlem->pos;
		trigger = get_trigger(mlem);
		if (trigger->type != TKN_BACKSLASH)
			move_forward(mlem, 1);
		return (trigger);
	}
	else if (token->trigger->len)
	{
		move_forward(mlem, token->trigger->len);
		token->start = mlem->pos;
		return (get_trigger(mlem));
	}
	token->start = mlem->pos;
	move_forward(mlem, 1);
	return (get_trigger(mlem));
}

static void
	create_symbol_token(
		t_mlem_parser *mlem, t_mlem_token *token)
{
	token->start = mlem->pos;
	move_past_trigger(mlem, token->trigger);
	token->end = mlem->pos;
	token->true_end = mlem->pos;
	token->len = token->end.content - token->start.content;
}

static void
	create_whitelist_token(
		t_mlem_parser *mlem, t_mlem_token *token)
{
	t_mlem_token_trigger	*trigger;

	trigger = set_token_start(mlem, token);
	while (trigger->type & token->trigger->whitelist)
	{
		move_past_trigger(mlem, trigger);
		trigger = get_trigger(mlem);
	}
	token->end = mlem->pos;
	token->true_end = mlem->pos;
	token->len = token->end.content - token->start.content;
}

static void
	create_blacklist_token(
		t_mlem_parser *mlem, t_mlem_token *token)
{
	t_mlem_token_trigger	*trigger;
	bool					error;

	error = false;
	trigger = set_token_start(mlem, token);
	while (!trigger_in_list(trigger, token->trigger->trg_blacklist))
	{
		error = true;
		if (trigger_in_list(trigger, token->trigger->trg_blacklist)
			|| trigger->type == TKN_EOF)
			break ;
		error = false;
		move_past_trigger(mlem, trigger);
		trigger = get_trigger(mlem);
	}
	token->end = mlem->pos;
	move_past_trigger(mlem, trigger);
	token->true_end = mlem->pos;
	token->len = token->end.content - token->start.content;
	if (error)
		set_error_t(mlem, token, ERR_UNCLOSED_SYMBOL);
}

t_mlem_token
	get_token(t_mlem_parser *mlem)
{
	t_mlem_token			token;

	token = (t_mlem_token){.true_start = mlem->pos};
	token.trigger = get_trigger(mlem);
	token.type = token.trigger->type;
	if (token.trigger->type == TKN_BACKSLASH)
		token.type = TKN_WORD;
	if (token.trigger->whitelist)
		create_whitelist_token(mlem, &token);
	else if (token.trigger->trg_blacklist[0])
		create_blacklist_token(mlem, &token);
	else
		create_symbol_token(mlem, &token);
	return (token);
}

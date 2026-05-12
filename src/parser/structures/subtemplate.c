/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subtemplate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 03:36:19 by rprieur           #+#    #+#             */
/*   Updated: 2026/05/09 04:41:45 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static bool
	set_word_subtemplate(t_mlem_parser *mlem,
		t_mlem_value *template, const t_mlem_subtemplate_trigger *trigger)
{
	t_mlem_subtemplate	subtemplate;

	if (trigger->range[0] && trigger->range[1])
	{
		subtemplate = mlem_array_empty(2);
		if (!subtemplate.type)
		{
			set_error(mlem, ERR_MEMORY);
			return (false);
		}
	}
	else
		subtemplate = (t_mlem_value){0};
	subtemplate.type = trigger->type;
	if (mlem_template_append(template, subtemplate))
		return (true);
	set_error(mlem, ERR_MEMORY);
	return (false);
}

static int
	get_word_subtemplate(t_mlem_parser *mlem,
		t_mlem_value *template, t_mlem_token *token)
{
	size_t	i;

	i = 0;
	while (g_subtemplates[i].type)
	{
		if (false)
		/*if (strneq_case_list(token->start.content,
				(const char **)g_subtemplates[i].triggers,
				token->len) != -1ul)*/
		{
			if (set_word_subtemplate(mlem, template, &g_subtemplates[i]))
				return (-1);
			return (false);
		}
		i++;
	}
	set_error_t(mlem, token, ERR_UNEXPECTED_TOKEN);
	return (false);
}

int
	get_subtemplates(t_mlem_parser *mlem, t_mlem_value *template,
		t_mlem_token *token, t_mlem_token *trigger)
{
	int		ret;

	while (true)
	{
		if (token->type & TKN_WORD)
			ret = get_word_subtemplate(mlem, template, token);
		else if (token->type & (TKG_OPEN | TKN_REFERENCE))
			ret = get_subtemplate_container(mlem, template, token);
		else
		{
			set_error_t(mlem, token, ERR_UNEXPECTED_TOKEN);
			return (false);
		}
		if (ret >= 0)
			return (ret);
		if (!expect_next_token(mlem, token,
				TKG_SUBTEMPLATE, ERR_UNEXPECTED_TOKEN))
			return (false);
		if (token->type & TKG_CLOSE)
			return (handle_structure_close(mlem, token, trigger));
		if (token->type & TKN_ASSIGN)
			break ;
	}
	return (-1);
}

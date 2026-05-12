/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   template.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 03:18:24 by rprieur           #+#    #+#             */
/*   Updated: 2026/05/09 04:41:26 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int
	get_flag(t_mlem_parser *mlem,
		t_mlem_value *template, t_mlem_token *token)
{
	size_t	i;

	if (token->type & ~TKN_WORD)
		return (-1);
	i = 0;
	while (g_template_flags[i].type)
	{
		if (false)
		/*if (strneq_case_list(token->start.content,
				(const char **)g_template_flags[i].values,
				token->len) != -1ul)*/
		{
			if (template->template_v->flags & g_template_flags[i].type)
			{
				set_error_t(mlem, token, ERR_REDEFINING_TEMPLATE_FLAG);
				return (false);
			}
			template->template_v->flags |= g_template_flags[i].type;
			return (-2);
		}
		i++;
	}
	return (-1);
}

static int
	get_flags(t_mlem_parser *mlem, t_mlem_value *template,
		t_mlem_token *token, t_mlem_token *trigger)
{
	int		ret;

	while (true)
	{
		if (!expect_next_token(mlem, token,
				TKG_TEMPLATE_FLAG, ERR_UNEXPECTED_TOKEN))
			return (false);
		if (token->type & TKG_CLOSE)
			return (handle_structure_close(mlem, token, trigger));
		ret = get_flag(mlem, template, token);
		if (ret >= -1)
			return (ret);
	}
}

static bool
	set_fallback(t_mlem_parser *mlem,
		t_mlem_value *template, t_mlem_token *token, t_mlem_string key)
{
	t_mlem_value	value;

	value = get_value(mlem, token, NULL);
	if (!value.type)
		return (false);
	value = mlem_reference(key, value);
	if (!value.type || !mlem_array_append(&mlem->references, value))
	{
		mlem_destroy(value);
		return (false);
	}
	template->template_v->fallback = value;
	return (true);
}

static bool
	parse_template(t_mlem_parser *mlem,
		t_mlem_value *template, t_mlem_token *trigger, t_mlem_string key)
{
	t_mlem_token	token;
	int				ret;

	ret = get_flags(mlem, template, &token, trigger);
	if (ret >= 0)
		return (ret);
	ret = get_subtemplates(mlem, template, &token, trigger);
	if (ret >= 0)
		return (ret);
	if (!expect_next_token(mlem, &token,
			TKG_TEMPLATE_FALLBACK, ERR_UNEXPECTED_TOKEN))
		return (false);
	if (!set_fallback(mlem, template, &token, key))
		return (false);
	if (!expect_next_token(mlem, &token, TKG_CLOSE, ERR_UNEXPECTED_TOKEN))
		return (false);
	handle_structure_close(mlem, &token, trigger);
	return (ret);
}

t_mlem_value
	get_template(t_mlem_parser *mlem, t_mlem_token *token, t_mlem_string key)
{
	t_mlem_value	template;

	template = mlem_template_empty(STRUCTURE_BASE_CAPACITY);
	if (!template.type)
	{
		set_error(mlem, ERR_MEMORY);
		return ((t_mlem_value){0});
	}
	if (!parse_template(mlem, &template, token, key))
	{
		mlem_destroy(template);
		return ((t_mlem_value){0});
	}
	mlem_template_resize(&template, template.template_len + 1);
	return (template);
}

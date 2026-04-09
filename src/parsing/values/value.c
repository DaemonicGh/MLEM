/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   value.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 13:59:06 by rprieur           #+#    #+#             */
/*   Updated: 2026/04/02 14:00:37 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"

static bool
	as_constant(t_mlem_token *token, t_mlem_value *value)
{
	size_t	i;

	i = 0;
	while (g_value_constants[i].key)
	{
		if (mlem_strncasecmp(token->val, g_value_constants[i].key, token->len)
			== 0)
		{
			*value = g_value_constants[i].value;
			return (true);
		}
		i++;
	}
	return (false);
}

static bool
	is_number(t_mlem_token *token)
{
	size_t	i;

	i = streq_list(token->val, g_pre_number_triggers);
	if (i != (size_t) -1)
		i = mlem_strlen(g_pre_number_triggers[i]);
	else
		i = 0;
	return (mlem_isdigit(token->val[i]));
}

t_mlem_value
	get_value(t_mlem_context *mlem, t_mlem_token *token)
{
	t_mlem_value	value;

	value = (t_mlem_value){0};
	if (token->type & TK_WORD)
	{
		if (as_constant(token, &value))
			return (value);
		if (is_number(token))
		{
			if (tktonbr(mlem, token, &value))
				return (value);
			return ((t_mlem_value){.val_int = mlem->error});
		}
	}
	value.type = MLEM_TYPE_STRING;
	value.val_string = tkstrndup_bs(mlem, token);
	if (!value.val_string)
		return ((t_mlem_value){.val_int = mlem->error});
	return (value);
}

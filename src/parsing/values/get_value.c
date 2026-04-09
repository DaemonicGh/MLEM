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

#include "errors.h"
#include "mlem.h"
#include "parser.h"
#include "tokens.h"
#include "utils.h"

static bool
	get_constant(t_mlem_context *mlem, t_mlem_token *token, t_mlem_value *value)
{
	size_t	i;

	if (!mlem->constants)
	{
		set_error_t(mlem, token, ERR_CONSTANT_WITHOUT_TABLE);
		return (false);
	}
	i = 0;
	while (mlem->constants->val_object[i].key)
	{
		if (mlem_strncmp(mlem->constants->val_object[i].key, token->val,
				token->len) == 0
			&& !mlem->constants->val_object[i].key[token->len])
		{
			*value = mlem->constants->val_object[i].value;
			value->reference = true;
			return (true);
		}
		i++;
	}
	set_error_t(mlem, token, ERR_UNDEFINED_CONSTANT);
	return (false);
}

static bool
	get_word_constant(t_mlem_token *token, t_mlem_value *value)
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

	if (token->type & TK_CONSTANT)
	{
		if (get_constant(mlem, token, &value))
			return (value);
		return ((t_mlem_value){.val_int = mlem->error});
	}
	else if (token->type & TK_WORD)
	{
		if (get_word_constant(token, &value))
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
	if (value.val_string)
		return (value);
	return ((t_mlem_value){.val_int = mlem->error});
}

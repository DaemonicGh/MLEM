/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nbr_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 12:05:14 by rprieur           #+#    #+#             */
/*   Updated: 2026/04/09 12:05:14 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>

#include "errors.h"
#include "utils.h"

int
	get_sign(t_mlem_token *token, size_t *i)
{
	if (token->val[*i] == '-')
	{
		(*i)++;
		return (-1);
	}
	if (token->val[*i] == '+')
		(*i)++;
	return (1);
}

int
	get_base(t_mlem_context *mlem, t_mlem_token *token, size_t *i)
{
	int	base;

	if (token->val[*i] == '0' && isalpha(token->val[*i + 1]))
	{
		(*i)++;
		base = strfind(g_number_base_triggers, toupper(token->val[*i]));
		if (base == -1)
		{
			set_error_t(mlem, token, ERR_INVALID_BASE_PREFIX);
			return (-1);
		}
		(*i)++;
		return (base);
	}
	return (10);
}

bool
	check_number_overflow(
		t_mlem_context *mlem, t_mlem_token *token, long val, long nval)
{
	if ((val < 0 && nval > val) || (val > 0 && nval < val))
	{
		set_error_t(mlem, token, ERR_NUMBER_OUT_OF_RANGE);
		return (false);
	}
	return (true);
}

bool
	check_number_overflowf(
		t_mlem_context *mlem, t_mlem_token *token, double val, double nval)
{
	if ((val < 0 && nval > val) || (val > 0 && nval < val))
	{
		set_error_t(mlem, token, ERR_NUMBER_OUT_OF_RANGE);
		return (false);
	}
	return (true);
}

bool
	is_end_valid(t_mlem_context *mlem, t_mlem_token *token, size_t i)
{
	if (i < token->len)
	{
		set_error_t(mlem, token, ERR_INVALID_NUMBER);
		return (false);
	}
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_double.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 11:46:19 by rprieur           #+#    #+#             */
/*   Updated: 2026/04/09 11:46:19 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "utils.h"

static void
	handle_decimal(t_mlem_token *token, double *val, size_t *i)
{
	double	dec;

	if (*val < 0)
		dec = -0.1;
	else
		dec = 0.1;
	(*i)++;
	while (token->val[*i] >= '0' && token->val[*i] <= '9' && *i < token->len)
	{
		*val = *val + (double)(token->val[*i] - '0') * dec;
		dec /= 10;
		(*i)++;
	}
}

static bool
	apply_exponent(
		t_mlem_context *mlem, t_mlem_token *token, double *val, long exp)
{
	double	nval;

	while (exp > 0)
	{
		nval = *val * 10;
		if (!check_number_overflowf(mlem, token, *val, nval))
			return (false);
		*val = nval;
		exp--;
	}
	while (exp < 0)
	{
		*val /= 10;
		exp++;
	}
	return (true);
}

static bool
	handle_exponent(
		t_mlem_context *mlem, t_mlem_token *token, double *val, size_t *i)
{
	int		sign;
	long	exp;
	long	nexp;

	(*i)++;
	sign = get_sign(token, i);
	exp = 0;
	nexp = 0;
	if (*i == token->len)
	{
		set_error_t(mlem, token, ERR_EMPTY_EXPONENT);
		return (false);
	}
	while (token->val[*i] >= '0' && token->val[*i] <= '9' && *i < token->len)
	{
		nexp = exp * 10 + (token->val[*i] - '0') * sign;
		if (!check_number_overflow(mlem, token, exp, nexp))
			return (false);
		exp = nexp;
		(*i)++;
	}
	return (apply_exponent(mlem, token, val, exp));
}

bool
	tktod(t_mlem_context *mlem, t_mlem_token *token, double *val)
{
	double	nval;
	int		sign;
	size_t	i;

	i = 0;
	sign = get_sign(token, &i);
	while (token->val[i] >= '0' && token->val[i] <= '9' && i < token->len)
	{
		nval = *val * 10 + (token->val[i] - '0') * sign;
		if (!check_number_overflowf(mlem, token, *val, nval))
			return (false);
		*val = nval;
		i++;
	}
	if (token->val[i] == '.' && i < token->len)
		handle_decimal(token, val, &i);
	if (mlem_strchr("eE", token->val[i]) && i < token->len)
	{
		if (!handle_exponent(mlem, token, val, &i))
			return (false);
	}
	return (is_end_valid(mlem, token, i));
}

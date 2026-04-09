/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_nbr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 11:45:42 by rprieur           #+#    #+#             */
/*   Updated: 2026/04/09 11:45:42 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"

static bool
	tktol_base(t_mlem_context *mlem, t_mlem_token *token, long *val)
{
	long		nval;
	int			sign;
	int			base;
	size_t		i;

	i = 0;
	sign = get_sign(token, &i);
	base = get_base(mlem, token, &i);
	if (base == -1)
		return (false);
	nval = strnfind(g_number_values, mlem_toupper(token->val[i]), base - 1);
	while (nval != -1 && i < token->len)
	{
		nval = *val * base + nval * sign;
		if (!check_number_overflow(mlem, token, *val, nval))
			return (false);
		*val = nval;
		i++;
		nval = strnfind(g_number_values, mlem_toupper(token->val[i]), base - 1);
	}
	return (is_end_valid(mlem, token, i));
}

bool
	tktonbr(t_mlem_context *mlem, t_mlem_token *token, t_mlem_value *value)
{
	if (strnfindset(token->val, ".eE", token->len) == (size_t) -1)
	{
		value->type = MLEM_TYPE_INT;
		return (tktol_base(mlem, token, &value->val_int));
	}
	else
	{
		value->type = MLEM_TYPE_FLOAT;
		return (tktod(mlem, token, &value->val_float));
	}
}

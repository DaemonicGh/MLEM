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

#include <ctype.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>

#include "context.h"
#include "errors.h"
#include "mlem.h"
#include "tokens.h"
#include "utils.h"

static bool
t_mlem_tktol_base(t_mlem_context *mlem, t_mlem_token *token, long *val)
{
	long		nval = 0;
	int			sign = 1;
	int			base = 10;
	size_t		i = 0;

	if (token->val[i] == '+')
	 	i++;
	else if (token->val[i] == '-')
	{
		sign = -1;
		i++;
	}

	if (token->val[i] == '0' && isalpha(token->val[i + 1]))
	{
		i++;
		if ((base = strfind(g_number_base_triggers, toupper(token->val[i]))) == -1)
		{
			set_error_t(mlem, token, ERR_INVALID_BASE_PREFIX);
			return (false);
		}
		i++;
	}

	while ((nval = strnfind(
		g_number_values, toupper(token->val[i]), base - 1)
	) != -1 && i < token->len)
	{
		nval = *val * base + nval * sign;
		if ((*val < 0 && nval > *val) || (*val > 0 && nval < *val))
		{
			set_error_t(mlem, token, ERR_NUMBER_OUT_OF_RANGE);
			return (false);
		}
		*val = nval;
		i++;
	}

	if (i < token->len)
	{
		set_error_t(mlem, token, ERR_INVALID_NUMBER);
		return (false);
	}
	return (true);
}

static bool
t_mlem_tktod(t_mlem_context *mlem, t_mlem_token *token, double *val)
{
	double	nval	= 0;
	int		sign	= 1;
	double	dec		= 0.1;
	size_t	i		= 0;
	long	exp		= 0;
	long	nexp	= 0;

	if (token->val[i] == '+')
	 	i++;
	else if (token->val[i] == '-')
	{
		sign = -1;
		dec = -0.1;
		i++;
	}

	while (token->val[i] >= '0' && token->val[i] <= '9' && i < token->len)
	{
		nval = *val * 10 + (token->val[i] - '0') * sign;
		if ((*val < 0 && nval > *val) || (*val > 0 && nval < *val))
		{
			set_error_t(mlem, token, ERR_NUMBER_OUT_OF_RANGE);
			return (false);
		}
		*val = nval;
		i++;
	}
	if (token->val[i] == '.' && i < token->len)
	{
		i++;
		while (token->val[i] >= '0' && token->val[i] <= '9' && i < token->len)
		{
			*val = *val + (double)(token->val[i] - '0') * dec;
			dec /= 10;
			i++;
			if ((exp < 0 && nexp > exp) || (exp > 0 && nexp < exp))
			{
				set_error_t(mlem, token, ERR_NUMBER_OUT_OF_RANGE);
				return (false);
			}
		}
	}
	if (strchr("eE", token->val[i]) && i < token->len)
	{
		i++;
		sign = 1;
		if (token->val[i] == '+')
		 	i++;
		else if (token->val[i] == '-')
		{
			sign = -1;
			i++;
		}
		if (i == token->len)
		{
			set_error_t(mlem, token, ERR_EMPTY_EXPONENT);
			return (false);
		}
		while (token->val[i] >= '0' && token->val[i] <= '9' && i < token->len)
		{
			nexp = exp * 10 + (token->val[i] - '0') * sign;
			if ((exp < 0 && nexp > exp) || (exp > 0 && nexp < exp))
			{
				set_error_t(mlem, token, ERR_NUMBER_OUT_OF_RANGE);
				return (false);
			}
			exp = nexp;
			i++;
		}
		while (exp > 0)
		{
			nval = *val * 10;
			if ((*val < 0 && nval > *val) || (*val > 0 && nval < *val))
			{
				set_error_t(mlem, token, ERR_NUMBER_OUT_OF_RANGE);
				return (false);
			}
			*val = nval;
			exp--;
		}
		while (exp < 0)
		{
			*val /= 10;
			exp++;
		}
	}

	if (i < token->len)
	{
		set_error_t(mlem, token, ERR_INVALID_NUMBER);
		return (false);
	}
	return (true);
}

static bool
t_mlem_tktonbr(t_mlem_context *mlem, t_mlem_token *token, t_mlem_value *value)
{
	if (strnfindset(token->val, ".eE", token->len) == ST_N1)
	{
		value->type = MLEM_TYPE_INT;
		return (t_mlem_tktol_base(mlem, token, &value->val_int));
	}
	else
	{
		value->type = MLEM_TYPE_FLOAT;
		return (t_mlem_tktod(mlem, token, &value->val_float));
	}
}

static bool
as_constant(t_mlem_token *token, t_mlem_value *value)
{
	for (size_t	i = 0; g_value_constants[i].key; i++)
	{
		if (strncasecmp(token->val, g_value_constants[i].key, token->len) == 0)
		{
			*value = g_value_constants[i].value;
			return (true);
		}
	}
	return (false);
}

static bool
is_number(t_mlem_token *token)
{
	size_t	i;

	i = streq_list(token->val, g_pre_number_triggers);
	if (i != ST_N1)
		i = strlen(g_pre_number_triggers[i]);
	else
		i = 0;
	return (isdigit(token->val[i]));
}

t_mlem_value
get_value(t_mlem_context *mlem, t_mlem_token *token)
{
	t_mlem_value	value = (t_mlem_value){0};

	if (token->type & TK_WORD)
	{
		if (as_constant(token, &value))
			return (value);
		if (is_number(token))
		{
			if (t_mlem_tktonbr(mlem, token, &value))
				return (value);
			return (MLEM_ERROR_VALUE(mlem->error));
		}
	}
	value.type = MLEM_TYPE_STRING;
	value.val_string = t_mlem_tkstrndup_bs(mlem, token);
	if (!value.val_string)
		return (MLEM_ERROR_VALUE(mlem->error));
	return (value);
}
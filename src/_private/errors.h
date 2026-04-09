/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 13:59:06 by rprieur           #+#    #+#             */
/*   Updated: 2026/04/02 14:00:37 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "context.h"
#include "tokens.h"

static const char	*g_error_messages[] = {
	"",
	"Unexpected error",
	"Unable to open file",
	"Memory error",
	"Given string is null",
	"Unexpected token",
	"Invalid backslash symbol",
	"Unclosed symbol",
	"Unclosed structure",
	"Incorrect closing symbol",
	"Object assignment in array",
	"Expected assignment symbol",
	"Expected value",
	"Key already in object",
	"Invalid number",
	"Numeric value out of 64-bit range",
	"Invalid value base prefix",
	"Empty value exponent",
	"Invalid value exponent"
};

t_mlem_error
set_error(t_mlem_error type);

t_mlem_error
set_error_l(t_mlem_context *mlem, t_mlem_error type);

t_mlem_error
set_error_t(t_mlem_context *mlem, t_mlem_token *token, t_mlem_error type);

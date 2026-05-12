/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extras.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 13:59:06 by rprieur           #+#    #+#             */
/*   Updated: 2026/05/09 23:08:24 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "data.h"

char
mlem_toupper(char c);

size_t
mlem_strlen(const char *str);

char
*mlem_strdup(const char *str);

char
*mlem_strnchrset(const char *str, const char *set, size_t n);

size_t
strctn(const char *s1, const char *s2);

size_t
streq_case(const char *s1, const char *s2);

bool
mlem_isdigit(char c);

t_mlem_token_trigger
*get_trigger_str(const char *str);

// SERIALIZER

typedef struct s_mlem_serializer
{
	FILE	*file;
	int		depth;
	bool	preceded;
	bool	from_reference;
}	t_mlem_serializer;

void
print_tab(t_mlem_serializer *mlem);

void
print_value(t_mlem_serializer *mlem, t_mlem_value value);

void
print_int(t_mlem_serializer *mlem, t_mlem_value value);

void
print_float(t_mlem_serializer *mlem, t_mlem_value value);

void
print_string(t_mlem_serializer *mlem, t_mlem_value string);

bool
print_type_value(t_mlem_serializer *mlem, t_mlem_value value);

void
print_object(t_mlem_serializer *mlem, t_mlem_value object);

void
print_array(t_mlem_serializer *mlem, t_mlem_value array);

void
print_subtemplate(t_mlem_serializer *mlem, t_mlem_subtemplate subtemplate);

void
print_template(t_mlem_serializer *mlem, t_mlem_value template);

// MATCHING

typedef struct s_mlem_match_value_candidate
{
	t_mlem_value	value;
	t_mlem_value	*parent;
	enum	e_weight
	{
		CANDF_CLAMPED		= 0x000010,
		CANDF_CONVERTED		= 0x000200,
		CANDF_OOB			= 0x040000,
		CANDF_UNSET			= 0x080000,
	}				weight;
}	t_mlem_candidate;

bool
match_restrictor(t_mlem_value *value, t_mlem_template *template);

bool
match_structure(t_mlem_candidate *candidate, t_mlem_subtemplate subtemplate);

bool
try_tweak(t_mlem_candidate *candidate, t_mlem_subtemplate subtemplate);

bool
try_conversion(t_mlem_candidate *candidate, t_mlem_subtemplate subtemplate);

bool
clamp_bounds(t_mlem_candidate *candidate, t_mlem_subtemplate subtemplate);

bool
check_bounds(t_mlem_candidate *candidate, t_mlem_subtemplate subtemplate);

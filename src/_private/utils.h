/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 13:59:06 by rprieur           #+#    #+#             */
/*   Updated: 2026/04/02 14:00:37 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stddef.h>
#include <stdbool.h>

#include "tokens.h"

size_t
streq(const char *s1, const char *s2);

size_t
strneq(const char *s1, const char *s2, size_t n);

size_t
streq_list(const char *s, const char **sa);

size_t
strneq_list(const char *s, const char **sa, size_t n);

size_t
set_transformed_bs_sequence(const char *str, char *result);

const char
*skip_potential_backslash(const char *s);

const char
*strchr_bs(const char *s, char c);

const char
*strstr_bs(const char *s1, const char *s2);

char
*tkstrndup_bs(t_mlem_context *mlem, t_mlem_token *token);

size_t
strfind(const char *s, char c);

size_t
strnfind(const char *s, char c, size_t n);

size_t
strnfindset(const char *s, char *set, size_t n);

size_t
mlem_strlen(const char *str);

char
*mlem_strchr(const char *str, int c);

int
mlem_strncmp(const char *str1, const char *str2, size_t size);

int
mlem_strncasecmp(const char *str1, const char *str2, size_t size);

int
mlem_isdigit(int c);

int
mlem_toupper(int c);

void
mlem_bzero(void *addr, size_t size);

int
get_sign(t_mlem_token *token, size_t *i);

int
get_base(t_mlem_context *mlem, t_mlem_token *token, size_t *i);

bool
check_number_overflow(
	t_mlem_context *mlem, t_mlem_token *token, long val, long nval);

bool
	check_number_overflowf(
		t_mlem_context *mlem, t_mlem_token *token, double val, double nval);

bool
	is_end_valid(t_mlem_context *mlem, t_mlem_token *token, size_t i);

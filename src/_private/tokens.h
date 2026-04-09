/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 13:59:06 by rprieur           #+#    #+#             */
/*   Updated: 2026/04/02 14:00:37 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <math.h>
#include <stddef.h>
#include <stdbool.h>

#include "mlem.h"
#include "context.h"

typedef enum e_mlem_token_type
{
	TK_NULL				= 0,
	TK_WORD				= 1 << 0,
	TK_OPEN_UNKNOWN		= 1 << 1,
	TK_CLOSE_UNKNOWN	= 1 << 2,
	TK_OPEN_ARRAY		= 1 << 3,
	TK_CLOSE_ARRAY		= 1 << 4,
	TK_OPEN_OBJECT		= 1 << 5,
	TK_CLOSE_OBJECT		= 1 << 6,
	TK_ASSIGN			= 1 << 7,
	TK_DEL_WORD			= 1 << 8,
	TK_ML_DEL_WORD		= 1 << 9,
	TK_COMMENT			= 1 << 10,
	TK_ML_COMMENT		= 1 << 11,
	TK_CONSTANT			= 1 << 12
}	t_mlem_token_type;

typedef enum e_mlem_token_type_group
{
	TKG_WORD			= TK_WORD | TK_DEL_WORD | TK_ML_DEL_WORD,
	TKG_OPEN			= TK_OPEN_UNKNOWN | TK_OPEN_ARRAY | TK_OPEN_OBJECT,
	TKG_CLOSE			= TK_CLOSE_UNKNOWN | TK_CLOSE_ARRAY | TK_CLOSE_OBJECT,
	TKG_COMMENT			= TK_COMMENT | TK_ML_COMMENT,
	TKG_VALUE			= TKG_WORD | TK_CONSTANT,
	TKG_ALLOCD_VALUE	= TKG_WORD,
	TKG_SIGNIFICANT		= TKG_VALUE | TKG_OPEN | TKG_CLOSE | TK_ASSIGN,
	TKG_ML				= TK_ML_DEL_WORD | TK_ML_COMMENT,
	TKG_WORD_EXTEND		= TK_DEL_WORD | TK_ML_DEL_WORD,
	TKG_BLANK_EXTEND	= TK_WORD | TK_CONSTANT,
	TKG_EXTENDS			= TKG_WORD_EXTEND | TKG_BLANK_EXTEND | TKG_COMMENT,
	TKG_ARRAY_VALUE		= TKG_VALUE,
	TKG_OBJECT_KEY		= TKG_WORD | TKG_CLOSE,
	TKG_OBJECT_VALUE	= TKG_WORD | TKG_OPEN | TK_CONSTANT
}	t_mlem_token_type_group;

typedef const struct s_mlem_token_trigger	t_mlem_token_trigger;

typedef struct s_mlem_token
{
	t_mlem_token_type		type;
	t_mlem_token_trigger	*trigger;
	char					*val;
	size_t					len;
}	t_mlem_token;

// Triggers

#define MAX_TRIGGER_AMT	3

struct s_mlem_token_trigger
{
	const t_mlem_token_type	type;
	const char				*start[MAX_TRIGGER_AMT + 1];
	const char				*end[MAX_TRIGGER_AMT + 1];
	const char				*error[MAX_TRIGGER_AMT + 1];
};

static const t_mlem_token_trigger			g_token_triggers[] = {
{
	.type = TK_ML_DEL_WORD,
	.start = {"'''"},
	.end = {"'''"}},
{
	.type = TK_ML_COMMENT,
	.start = {"///"},
	.end = {"///"}},
{
	.type = TK_ML_DEL_WORD,
	.start = {"\"\"\""},
	.end = {"\"\"\""}},
{
	.type = TK_COMMENT,
	.start = {"//"},
	.end = {"\n", "//"}},
{
	.type = TK_ML_COMMENT,
	.start = {"/*"},
	.end = {"*/"}},
{
	.type = TK_ML_COMMENT,
	.start = {"*/"}},
{
	.type = TK_OPEN_UNKNOWN,
	.start = {"["}},
{
	.type = TK_CLOSE_UNKNOWN,
	.start = {"]"}},
{
	.type = TK_ASSIGN,
	.start = {"="}},
{
	.type = TK_DEL_WORD,
	.start = {"'"},
	.end = {"'"},
	.error = {"\n"}},
{
	.type = TK_ML_DEL_WORD,
	.start = {"\""},
	.end = {"\""}},
{
	.type = TK_CONSTANT,
	.start = {"#"}},
{
	.type = TK_OPEN_OBJECT,
	.start = {"{"}},
{
	.type = TK_CLOSE_OBJECT,
	.start = {"}"}},
{
	.type = TK_ASSIGN,
	.start = {":"}},
{0}
};

static const char							*g_skip_triggers[] = {
	" ", "\t", "\n", ",", NULL
};

static const char							*g_backslash_transforms[][2] = {
{"\n", ""},
{"\\", "\\"},
{"\"", "\""},
{"'", "'" },
{"n", "\n"},
{"t", "\t"},
{"r", "\r"},
{"b", "\b"},
{"f", "\f"},
{0}
};

static const char							*g_token_repr[] = {
	"N", "W", "[", "]", "(", ")", "{", "}", "=",
	"'", "\"", "//", "///", "/*", "*/", "#", NULL
};

static const t_mlem_pair					g_value_constants[] = {
{.key = "null",
	.value = {.type = MLEM_TYPE_NULL}},
{.key = "false",
	.value = {.type = MLEM_TYPE_BOOL,	.val_bool = false}},
{.key = "true",
	.value = {.type = MLEM_TYPE_BOOL,	.val_bool = true}},
{.key = "inf",
	.value = {.type = MLEM_TYPE_FLOAT,	.val_float = INFINITY}},
{.key = "-inf",
	.value = {.type = MLEM_TYPE_FLOAT,	.val_float = -INFINITY}},
{.key = "nan",
	.value = {.type = MLEM_TYPE_FLOAT,	.val_float = NAN}},
{0}
};

static const char							*g_pre_number_triggers[] = {
	"-.", "+.", "-", ".", "+", NULL
};
static const char							*g_number_values
	= "0123456789ABCDEF";
static const char							*g_number_base_triggers
	= "  BTQ   O   D   X";

void
print_token(t_mlem_token_type token);

bool
move_forward(t_mlem_context *mlem, size_t amount);

bool
move_past_blank(t_mlem_context *mlem);

bool
move_past_word(t_mlem_context *mlem);

bool
move_past_extend(
	t_mlem_context *mlem, t_mlem_token *token, const char **trigger_str);

t_mlem_token_trigger
*get_start_trigger(const char *s);

t_mlem_token_trigger
*get_start_trigger_p(const char *s, const char **trigger_str);

t_mlem_token
get_next_token(t_mlem_context *mlem);

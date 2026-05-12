/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 13:59:06 by rprieur           #+#    #+#             */
/*   Updated: 2026/05/09 23:02:20 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdlib.h>

#include "data.h"
#include "extras.h"

typedef struct s_mlem_position
{
	char				*content;
	uint32_t			line;
	uint32_t			column;
}	t_mlem_position;

typedef struct s_mlem_token
{
	t_mlem_token_type		type;
	t_mlem_token_trigger	*trigger;
	t_mlem_position			start;
	t_mlem_position			end;
	t_mlem_position			true_start;
	t_mlem_position			true_end;
	size_t					len;
}	t_mlem_token;

typedef struct s_mlem_parser
{
	const char			*filename;
	t_mlem_value		outer_references;
	t_mlem_value		references;
	char				*start;
	t_mlem_position		pos;
	int32_t				depth;
	t_mlem_error		error;
}	t_mlem_parser;

// UTILS

t_mlem_error
set_error(t_mlem_parser *mlem, t_mlem_error type);

t_mlem_error
set_error_p(t_mlem_parser *mlem,
	t_mlem_position start, t_mlem_position end, t_mlem_error type);

t_mlem_error
set_error_t(t_mlem_parser *mlem, t_mlem_token *token, t_mlem_error type);

t_mlem_error
set_error_v(t_mlem_parser *mlem, t_mlem_error type, t_mlem_value value);

int
transform(t_mlem_string string, t_mlem_string dest);

bool
str_eq_tkn_case(t_mlem_string string, t_mlem_token *token);

// PARSER

t_mlem_parser
init_context(const char *filename, char *content,
	const t_mlem_value outer_references);

bool
append_pair(
	t_mlem_parser *mlem, t_mlem_value *object,
	t_mlem_token *key, t_mlem_token *value);

bool
append_pair_reference(
	t_mlem_parser *mlem, t_mlem_value *object,
	t_mlem_token *key, t_mlem_token *value);

// VALUES

bool
get_word_special_value(t_mlem_parser *mlem,
	t_mlem_token *token, t_mlem_value *value);

t_mlem_value
get_word_value(
	t_mlem_parser *mlem, t_mlem_token *token, t_mlem_string key);

t_mlem_value
get_value(t_mlem_parser *mlem, t_mlem_token *token, t_mlem_string key);

// STRINGS

t_mlem_value
get_string_value(
	t_mlem_parser *mlem, t_mlem_token *token, t_mlem_string key);

// NUMBERS

int
get_sign(t_mlem_token *token, size_t *i);

int
get_base(t_mlem_token *token, size_t *i);

t_mlem_value
get_int_value(t_mlem_parser *mlem, t_mlem_token *token);

t_mlem_value
get_float_value(t_mlem_parser *mlem, t_mlem_token *token);

t_mlem_value
get_number_value(
	t_mlem_parser *mlem, t_mlem_token *token, t_mlem_string key);

// REFERENCES

t_mlem_value
get_deep_reference(
	const t_mlem_value references, t_mlem_token *token);

t_mlem_value
get_reference(const t_mlem_value references, t_mlem_token *token);

t_mlem_value
get_reference_value(
	t_mlem_parser *mlem, t_mlem_token *token, t_mlem_string key);

// STRUCTURES
t_mlem_value
get_structure(t_mlem_parser *mlem, t_mlem_token *token, t_mlem_string key);

t_mlem_value
get_array(t_mlem_parser *mlem, t_mlem_token *token, t_mlem_string key);

t_mlem_value
get_object(t_mlem_parser *mlem, t_mlem_token *token, t_mlem_string key);

bool
get_subtemplate_data(
	t_mlem_subtemplate subtemplate, t_mlem_value value);

int
get_subtemplate_container(t_mlem_parser *mlem, t_mlem_value *template,
	t_mlem_token *token);

int
get_subtemplates(t_mlem_parser *mlem, t_mlem_value *template,
	t_mlem_token *token, t_mlem_token *trigger);

t_mlem_value
get_template(t_mlem_parser *mlem, t_mlem_token *token, t_mlem_string key);

bool
handle_structure_close(t_mlem_parser *mlem,
	t_mlem_token *token, t_mlem_token *trigger);

// TOKENIZER

void
move_forward(t_mlem_parser *mlem, size_t amount);

void
move_past_trigger(t_mlem_parser *mlem, t_mlem_token_trigger *trigger);

t_mlem_token_trigger
*get_trigger(t_mlem_parser *mlem);

bool
trigger_in_list(t_mlem_token_trigger *trigger, const uint8_t *list);

t_mlem_token
get_token(t_mlem_parser *mlem);

t_mlem_token
get_next_token(t_mlem_parser *mlem);

bool
expect_next_token(t_mlem_parser *mlem, t_mlem_token *token,
	uint32_t whitelist, t_mlem_error error);

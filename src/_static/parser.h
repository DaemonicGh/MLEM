/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 13:59:06 by rprieur           #+#    #+#             */
/*   Updated: 2026/04/02 14:00:37 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "mlem.h"
#include "tokens.h"

t_mlem_value
get_value(t_mlem_context *mlem, t_mlem_token *token);

t_mlem_value
parse_array(t_mlem_context *mlem, t_mlem_token *trigger_token);

t_mlem_value
parse_object(t_mlem_context *mlem, t_mlem_token *trigger_token);

t_mlem_value
parse_structure(t_mlem_context *mlem, t_mlem_token *trigger_token);

void
parse_start(t_mlem_context *mlem);

t_mlem_context
init_context(char *content, t_mlem_settings settings);

char
*open_and_read_file(const char *filename, t_mlem_error *error);

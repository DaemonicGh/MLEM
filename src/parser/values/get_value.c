/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 13:59:06 by rprieur           #+#    #+#             */
/*   Updated: 2026/05/07 18:32:55 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_mlem_value
	get_value(t_mlem_parser *mlem, t_mlem_token *token, t_mlem_string key)
{
	if (token->type & TKN_WORD)
		return (get_word_value(mlem, token, key));
	else if (token->type & TKN_NUMBER)
		return (get_number_value(mlem, token, key));
	else if (token->type & TKN_STRING)
		return (get_string_value(mlem, token, key));
	else if (token->type & TKN_REFERENCE)
		return (get_reference_value(mlem, token, key));
	else if (token->type & TKG_OPEN)
		return (get_structure(mlem, token, key));
	set_error_t(mlem, token, ERR_UNEXPECTED_ERROR);
	return ((t_mlem_value){0});
}

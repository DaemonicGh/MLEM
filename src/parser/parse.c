/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 13:59:06 by rprieur           #+#    #+#             */
/*   Updated: 2026/05/09 03:59:48 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlem.h"
#include "parser.h"
#include "data.h"

static bool
	check_recursive_references(t_mlem_parser *mlem, t_mlem_value reference)
{
	const t_mlem_reference	original = reference.reference_v;
	int						count;

	count = 0;
	while (reference.type == MLEM_TYPE_REFERENCE)
	{
		if (reference.reference_v == original)
		{
			set_error_v(mlem, ERR_RECURSIVE_REFERENCE, reference);
			return (false);
		}
		if (count > 255)
		{
			set_error_v(mlem, ERR_REFERENCE_RECURSION_LIMIT, reference);
			return (false);
		}
		reference = reference.reference_v->value;
		count++;
	}
	return (true);
}

static bool
	check_references(t_mlem_parser *mlem)
{
	size_t		i;

	i = 0;
	while (i < mlem->references.array_len)
	{
		if (!check_recursive_references(mlem,
				mlem->references.array_v[i].reference_v->value))
			return (false);
		if (!mlem->references.array_v[i].reference_v->value.type)
		{
			set_error_v(mlem, ERR_UNDEFINED_REFERENCE,
				mlem->references.array_v[i].reference_v->value);
			return (false);
		}
		i++;
	}
	return (true);
}

t_mlem_value
	mlem_parse(const char *filename, char **content,
		const t_mlem_value outer_references)
{
	t_mlem_parser	mlem;
	t_mlem_value	structure;

	mlem = init_context(filename, NULL, outer_references);
	if (mlem.error)
		return ((t_mlem_value){.int_v = mlem.error});
	structure = get_structure(&mlem, &(t_mlem_token){
			.type = TKN_OPEN,
			.trigger = &g_mlem_data.tokens[TRG_OPEN_STRUCTURE]},
			NULL);
	check_references(&mlem);
	mlem_destroy(mlem.references);
	if (content)
		*content = mlem.start;
	else
		free(mlem.start);
	if (mlem.error)
		return ((t_mlem_value){.int_v = mlem.error});
	return (structure);
}

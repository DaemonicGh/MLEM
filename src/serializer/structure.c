/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 00:51:29 by rprieur           #+#    #+#             */
/*   Updated: 2026/05/09 22:33:36 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "extras.h"
#include <stdio.h>

static void
	print_key(t_mlem_serializer *mlem, t_mlem_string key, bool reference)
{
	t_mlem_value	string;

	if (reference)
	{
		print_tab(mlem);
		fputc('#', mlem->file);
		string = mlem_string(key);
		string.string_flavor = MLEM_STR_UNQUOTED;
		print_string(mlem, string);
	}
	else
	{
		string = mlem_string(key);
		string.string_flavor = MLEM_STR_DQUOTED;
		print_string(mlem, string);
	}
	fwrite(" = ", 1, 3, mlem->file);
}

void
	print_object(t_mlem_serializer *mlem, t_mlem_value object)
{
	size_t		i;

	mlem->depth++;
	i = 0;
	while (i < object.object_len)
	{
		if (object.object_v[i].value.type == MLEM_TYPE_REFERENCE
			&& object.object_v[i].value.reference_owner)
		{
			print_key(mlem, object.object_v[i].key, true);
			mlem->preceded = true;
			print_value(mlem, object.object_v[i++].value.reference_v->value);
		}
		else
		{
			print_key(mlem, object.object_v[i].key, false);
			mlem->preceded = true;
			print_value(mlem, object.object_v[i++].value);
		}
	}
	mlem->depth--;
}

void
	print_array(t_mlem_serializer *mlem, t_mlem_value array)
{
	size_t		i;

	mlem->depth++;
	i = 0;
	while (i < array.array_len)
		print_value(mlem, array.array_v[i++]);
	mlem->depth--;
}

static void
	print_template_structure(
		t_mlem_serializer *mlem, t_mlem_template_struct structure)
{
	size_t		i;

	i = 0;
	if (structure.type == MLEM_TYPE_REFERENCE)
	{
		print_value(mlem, structure);
		return ;
	}
	while (g_template_structures[i].type
		&& structure.type != g_template_structures[i].type)
		i++;
	print_tab(mlem);
	if (g_template_structures[i].type)
	{
		fputs(g_template_structures[i].triggers[0], mlem->file);
		print_array(mlem, structure);
	}
	else
		fwrite("???\n", 1, 4, mlem->file);
}

static void
	print_template_flags(t_mlem_serializer *mlem, t_mlem_template_flag flags)
{
	size_t		i;

	i = 0;
	print_tab(mlem);
	while (g_template_flags[i].type)
	{
		if (flags & g_template_flags[i].type)
		{
			fputs(g_template_flags[i].values[0], mlem->file);
			flags &= ~g_template_flags[i].type;
		}
		i++;
	}
	fputc('\n', mlem->file);
}

void
	print_template(t_mlem_serializer *mlem, t_mlem_value template)
{
	size_t		i;

	print_tab(mlem);
	fputs("<\n", mlem->file);
	if (template.template_v->structure.type)
		print_template_structure(mlem, template.template_v->structure);
	if (template.template_v->flags)
		print_template_flags(mlem, template.template_v->flags);
	i = 0;
	while (i < template.template_len)
		print_subtemplate(mlem, template.template_v->subtemplates[i++]);
	if (template.template_v->fallback.type)
	{
		print_tab(mlem);
		fwrite("= ", 1, 2, mlem->file);
		mlem->preceded = true;
		print_value(mlem, template.template_v->fallback.reference_v->value);
	}
	fwrite(">\n", 1, 2, mlem->file);
}

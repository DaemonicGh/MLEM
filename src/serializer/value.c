/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   value.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 12:03:02 by rprieur           #+#    #+#             */
/*   Updated: 2026/05/09 23:05:23 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "extras.h"

static bool
	print_escaped(
		t_mlem_serializer *mlem, t_mlem_value value, t_mlem_string string)
{
	char		transform;

	transform = g_mlem_data.repr_data.transform[(int)string[0]];
	if (transform == 'x')
		fprintf(mlem->file, "\\x%02X", string[0]);
	else if (transform != ' ')
	{
		fputc('\\', mlem->file);
		fputc(transform, mlem->file);
	}
	else if (value.string_flavor == MLEM_STR_UNQUOTED
		&& !(get_trigger_str(string)->type
			& g_mlem_data.tokens[TRG_WORD].whitelist))
	{
		fputc('\\', mlem->file);
		fputc(string[0], mlem->file);
	}
	else
		return (false);
	return (true);
}

void
	print_string(t_mlem_serializer *mlem, t_mlem_value string)
{
	const char	*flavor = g_mlem_data.repr_data.flavor[string.string_flavor];
	size_t		i;

	i = 0;
	print_tab(mlem);
	fputs(flavor, mlem->file);
	if (string.string_flavor & MLEM_STR_UNQUOTED
		&& get_trigger_str(string.string_v)->type != TKN_WORD)
		fputc('\\', mlem->file);
	while (string.string_v[i])
	{
		if (strctn(string.string_v, flavor))
			fputc('\\', mlem->file);
		if (string.string_v[i] < 0
			|| !(string.string_flavor & MLEM_STR_ESCAPE)
			|| !print_escaped(mlem, string, &string.string_v[i]))
			fputc(string.string_v[i], mlem->file);
		i++;
	}
	fputs(flavor, mlem->file);
}

static void
	print_reference(t_mlem_serializer *mlem, t_mlem_value reference)
{
	t_mlem_value	value;

	print_tab(mlem);
	fputc('#', mlem->file);
	value = mlem_string(reference.reference_v->name);
	value.string_flavor = MLEM_STR_UNQUOTED;
	print_string(mlem, value);
	value = reference.reference_v->value;
	if (!mlem->from_reference && value.type & TYPEG_REF_PRINTABLE
		&& (value.type != MLEM_TYPE_STRING
			|| !(value.string_flavor & MLEM_STR_MULTILINE)))
	{
		mlem->from_reference = true;
		mlem->preceded = true;
		fwrite(" // ", 4, 1, mlem->file);
		print_type_value(mlem, value);
		mlem->from_reference = false;
	}
	else
		fputc('\n', mlem->file);
}

static bool
	print_word_constant(t_mlem_serializer *mlem, t_mlem_value value)
{
	size_t			i;
	size_t			j;

	i = 1;
	while (true)
	{
		j = 0;
		while (j < CONSTANT_COUNT && g_mlem_data.constants[i][j].name[0])
		{
			if (mlem_equal(value, g_mlem_data.constants[i][j].value))
			{
				print_tab(mlem);
				fputs(g_mlem_data.constants[i][j].name, mlem->file);
				fputc('\n', mlem->file);
				return (true);
			}
			j++;
		}
		if (j == 0)
			break ;
		i++;
	}
	return (false);
}

bool
	print_type_value(t_mlem_serializer *mlem, t_mlem_value value)
{
	if (value.type == MLEM_TYPE_REFERENCE)
		print_reference(mlem, value);
	else if (print_word_constant(mlem, value))
		return (true);
	else if (value.type == MLEM_TYPE_STRING)
	{
		print_string(mlem, value);
		fputc('\n', mlem->file);
	}
	else if (value.type == MLEM_TYPE_INT)
		print_int(mlem, value);
	else if (value.type == MLEM_TYPE_FLOAT)
		print_float(mlem, value);
	else if (value.type == MLEM_TYPE_NONE)
	{
		print_tab(mlem);
		fwrite("Error: ", 6, 1, mlem->file);
		fputs(g_error_messages[value.int_v][0], mlem->file);
		fputc('\n', mlem->file);
	}
	else
		return (false);
	return (true);
}

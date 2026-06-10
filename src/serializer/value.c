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

#include ".mlem_values.h"
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
	else if (value.strv.flavor == MLEM_STR_UNQUOTED
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
	const char	*flavor = g_mlem_data.repr_data.flavor[string.strv.flavor];
	size_t		i;

	i = 0;
	fputs(flavor, mlem->file);
	if (string.strv.flavor & MLEM_STR_UNQUOTED
		&& get_trigger_str(string.strv.value)->type != TKN_WORD)
		fputc('\\', mlem->file);
	while (string.strv.value[i])
	{
		if (strctn(string.strv.value, flavor))
			fputc('\\', mlem->file);
		if (string.strv.value[i] < 0
			|| !(string.strv.flavor & MLEM_STR_ESCAPE)
			|| !print_escaped(mlem, string, &string.strv.value[i]))
			fputc(string.strv.value[i], mlem->file);
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
	value = mlem_string(reference.refv.value->name);
	value.strv.flavor = MLEM_STR_UNQUOTED;
	print_string(mlem, value);
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
		print_tab(mlem);
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
		fputs(g_error_messages[value.intv.value][0], mlem->file);
		fputc('\n', mlem->file);
	}
	else
		return (false);
	return (true);
}

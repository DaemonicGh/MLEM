/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 23:37:28 by rprieur           #+#    #+#             */
/*   Updated: 2026/05/10 00:19:49 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "extras.h"

static void
	print_base_int(FILE *file, t_mlem_value value)
{
	t_mlem_value	send;

	if (value.intv.value >= value.intv.base)
	{
		send = value;
		send.intv.value /= value.intv.base;
		print_base_int(file, send);
	}
	fputc(g_mlem_data.repr_data.number[
		value.intv.value % value.intv.base], file);
}

void
	print_int(t_mlem_serializer *mlem, t_mlem_value value)
{
	const char		base_char = g_mlem_data.repr_data.base[value.intv.base];
	t_mlem_value	absolute;

	print_tab(mlem);
	if (base_char == ' ')
	{
		fprintf(mlem->file, "%zi\n", value.intv.value);
		return ;
	}
	absolute = value;
	if (value.intv.value < 0)
	{
		fputc('-', mlem->file);
		absolute.intv.value = -absolute.intv.value;
	}
	fprintf(mlem->file, "0%c", base_char);
	print_base_int(mlem->file, absolute);
	fputc('\n', mlem->file);
}

static void
	fix_float_exponent(t_mlem_value *value)
{
	int		i;

	i = 0;
	while (i < value->floatv.exponent)
	{
		value->floatv.value /= 10;
		i++;
	}
	while (i > value->floatv.exponent)
	{
		value->floatv.value *= 10;
		i--;
	}
}

static void
	print_float_decimal(t_mlem_serializer *mlem, t_mlem_value value)
{
	int		dec;
	int		udec;
	int		zeros;
	int		digits;

	zeros = 0;
	digits = 0;
	while (value.floatv.value && ++zeros < 4 && ++digits < 12)
	{
		value.floatv.value *= 10;
		dec = value.floatv.value;
		if (!dec)
			continue ;
		udec = value.floatv.value + 0.001;
		if (udec != dec && udec < 10)
		{
			fprintf(mlem->file, "%0*i", zeros, udec);
			return ;
		}
		fprintf(mlem->file, "%0*i", zeros, dec);
		value.floatv.value -= dec;
		zeros = 0;
	}
}

void
	print_float(t_mlem_serializer *mlem, t_mlem_value value)
{
	fix_float_exponent(&value);
	print_tab(mlem);
	if ((long)value.floatv.value || value.floatv.value == 0)
		fprintf(mlem->file, "%zi", (long)value.floatv.value);
	if (value.floatv.value < 0)
		value.floatv.value = -value.floatv.value;
	value.floatv.value = fmod(value.floatv.value, 1);
	if (value.floatv.value || value.floatv.exponent == 0)
		fputc('.', mlem->file);
	print_float_decimal(mlem, value);
	if (value.floatv.exponent)
		fprintf(mlem->file, "e%i", value.floatv.exponent);
	fputc('\n', mlem->file);
}

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

	if (value.int_v >= value.int_base)
	{
		send = value;
		send.int_v /= value.int_base;
		print_base_int(file, send);
	}
	fputc(g_mlem_data.repr_data.number[value.int_v % value.int_base], file);
}

void
	print_int(t_mlem_serializer *mlem, t_mlem_value value)
{
	const char		base_char = g_mlem_data.repr_data.base[value.int_base];
	t_mlem_value	absolute;

	print_tab(mlem);
	if (base_char == ' ')
	{
		fprintf(mlem->file, "%zi\n", value.int_v);
		return ;
	}
	absolute = value;
	if (value.int_v < 0)
	{
		fputc('-', mlem->file);
		absolute.int_v = -absolute.int_v;
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
	while (i < value->float_exponent)
	{
		value->float_v /= 10;
		i++;
	}
	while (i > value->float_exponent)
	{
		value->float_v *= 10;
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
	while (value.float_v && ++zeros < 4 && ++digits < 12)
	{
		value.float_v *= 10;
		dec = value.float_v;
		if (!dec)
			continue ;
		udec = value.float_v + 0.001;
		if (udec != dec && udec < 10)
		{
			fprintf(mlem->file, "%0*i", zeros, udec);
			return ;
		}
		fprintf(mlem->file, "%0*i", zeros, dec);
		value.float_v -= dec;
		zeros = 0;
	}
}

void
	print_float(t_mlem_serializer *mlem, t_mlem_value value)
{
	fix_float_exponent(&value);
	print_tab(mlem);
	if ((long)value.float_v || value.float_v == 0)
		fprintf(mlem->file, "%zi", (long)value.float_v);
	if (value.float_v < 0)
		value.float_v = -value.float_v;
	value.float_v = fmod(value.float_v, 1);
	if (value.float_v || value.float_exponent == 0)
		fputc('.', mlem->file);
	print_float_decimal(mlem, value);
	if (value.float_exponent)
		fprintf(mlem->file, "e%i", value.float_exponent);
	fputc('\n', mlem->file);
}

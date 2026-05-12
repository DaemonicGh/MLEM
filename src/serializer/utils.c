/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 01:23:59 by rprieur           #+#    #+#             */
/*   Updated: 2026/05/10 01:23:59 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "extras.h"

void
	print_tab(t_mlem_serializer *mlem)
{
	static const char	tab[32] = ""
		"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t";

	if (mlem->preceded)
	{
		mlem->preceded = false;
		return ;
	}
	if (mlem->depth > 32)
		mlem->depth = 32;
	fwrite(tab, 1, mlem->depth, mlem->file);
}

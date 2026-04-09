/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 14:39:09 by rprieur           #+#    #+#             */
/*   Updated: 2026/04/09 14:39:09 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	mlem_bzero(void *addr, size_t size)
{
	unsigned char	*ucaddr;
	size_t			i;

	ucaddr = addr;
	i = 0;
	while (i < size)
		ucaddr[i++] = 0;
}

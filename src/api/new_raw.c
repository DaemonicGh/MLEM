/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_raw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 14:26:06 by rprieur           #+#    #+#             */
/*   Updated: 2026/06/04 14:26:06 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlem.h"

t_mlem_value
	mlem_raw_value(t_mlem_value_type type, uint64_t value)
{
	return ((t_mlem_value){
		._datav = {
			.type = type,
			.value = value
		}
	});
}

t_mlem_value
	mlem_raw_value_ex(t_mlem_value_type type,
		uint64_t value, uint32_t data_32, uint16_t data_16)
{
	return ((t_mlem_value){
		._datav = {
			.type = type,
			.data32 = data_32,
			.data16 = data_16,
			.value = value
		}
	});
}

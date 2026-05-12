/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 13:59:06 by rprieur           #+#    #+#             */
/*   Updated: 2026/05/04 18:21:19 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "data.h"

bool
	mlem_template_resize(t_mlem_value *template, uint32_t new_capacity)
{
	void	*tmp;

	if (new_capacity > template->template_len + UINT16_MAX)
		new_capacity = template->template_len + UINT16_MAX;
	template = mlem_dereference_ptr(template);
	tmp = realloc(template, sizeof(t_mlem_template)
			+ sizeof(t_mlem_subtemplate) * new_capacity);
	if (!tmp)
		return (false);
	template->template_v = tmp;
	if (new_capacity > template->template_len)
		template->template_extra_capacity
			= new_capacity - template->template_len;
	else
		template->template_extra_capacity = 0;
	return (true);
}

bool
	mlem_template_append(t_mlem_value *template, t_mlem_subtemplate value)
{
	template = mlem_dereference_ptr(template);
	if (template->template_extra_capacity == 0)
	{
		if (!mlem_template_resize(
				template, template->template_len * STRUCTURE_GROW_RATIO))
			return (false);
	}
	template->template_v->subtemplates[template->template_len] = value;
	template->template_len++;
	template->template_extra_capacity--;
	return (true);
}

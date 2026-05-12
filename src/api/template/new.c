/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 18:31:27 by rprieur           #+#    #+#             */
/*   Updated: 2026/05/04 18:21:26 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdarg.h>

#include "mlem.h"

t_mlem_value
	mlem_template_empty(uint32_t capacity)
{
	t_mlem_value	template;

	template.type = MLEM_TYPE_TEMPLATE;
	template.template_v = malloc(sizeof(t_mlem_template)
			+ sizeof(t_mlem_subtemplate) * capacity);
	if (!template.template_v)
		return ((t_mlem_value){0});
	template.template_extra_capacity = capacity;
	template.template_len = 0;
	template.template_v->flags = MLEM_TPF_NONE;
	template.template_v->structure = (t_mlem_subtemplate){0};
	template.template_v->fallback = (t_mlem_value){0};
	return (template);
}

t_mlem_value
	mlem_template_va(uint32_t len, ...)
{
	t_mlem_value	template;
	va_list			va;
	size_t			i;

	template = mlem_template_empty(len);
	if (!template.template_v)
		return ((t_mlem_value){0});
	i = 0;
	va_start(va, len);
	while (i < len)
		template.template_v->subtemplates[i++]
			= va_arg(va, t_mlem_subtemplate);
	va_end(va);
	return (template);
}

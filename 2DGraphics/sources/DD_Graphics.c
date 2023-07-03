/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DD_Graphics.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 18:32:20 by tchoquet          #+#    #+#             */
/*   Updated: 2023/06/29 22:47:52 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DD_Graphics_internal.h"

t_2d_context	*create_2d_context(void *pixels_buffer, t_uint32 width,
					t_uint32 height)
{
	t_i_2d_context	*new_context;

	if (pixels_buffer == NULL)
		return (NULL);
	new_context = malloc(sizeof(t_i_2d_context));
	if (new_context == NULL)
		return (NULL);
	new_context->buffer = pixels_buffer;
	new_context->width = width;
	new_context->height = height;
	return ((t_2d_context *)new_context);
}

void	delete_2d_context(t_2d_context *context)
{
	t_i_2d_context	*i_context;

	i_context = (t_i_2d_context *)context;
	free(i_context);
}

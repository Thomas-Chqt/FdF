/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infos.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:06:29 by tchoquet          #+#    #+#             */
/*   Updated: 2023/06/26 16:06:54 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DD_Graphics_internal.h"

t_uint32	get_length(t_2d_point a, t_2d_point b)
{
	int	dx;
	int	dy;

	dx = abs(b.x - a.x);
	dy = abs(b.y - a.y);
	return (
		(t_uint32)sqrt(dx * dx + dy * dy)
	);
}

t_uint32	get_2d_context_height(t_2d_context *context)
{
	t_i_2d_context	*i_context;

	i_context = (t_i_2d_context *)context;
	return (i_context->height);
}

t_uint32	get_2d_context_width(t_2d_context *context)
{
	t_i_2d_context	*i_context;

	i_context = (t_i_2d_context *)context;
	return (i_context->width);
}

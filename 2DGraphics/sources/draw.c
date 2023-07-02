/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 21:00:58 by tchoquet          #+#    #+#             */
/*   Updated: 2023/06/26 17:31:04 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DD_Graphics_internal.h"

static t_printable_2d_line	setup_line(t_2d_point a, t_2d_point b)
{
	t_printable_2d_line	setuped_line;

	setuped_line.dx = abs(b.x - a.x);
	setuped_line.dy = abs(b.y - a.y);
	if (a.x < b.x)
		setuped_line.sx = 1;
	else
		setuped_line.sx = -1;
	if (a.y < b.y)
		setuped_line.sy = 1;
	else
		setuped_line.sy = -1;
	setuped_line.err = setuped_line.dx - setuped_line.dy;
	setuped_line.current = a;
	setuped_line.line_len = get_length(a, b);
	return (setuped_line);
}

void	put_2d_point(t_2d_context *context, t_2d_point point)
{
	t_i_2d_context	*i_context;

	if (point.x < 0 || point.y < 0)
		return ;
	if (point.x > (int)get_2d_context_width(context) - 1)
		return ;
	if (point.y > (int)get_2d_context_height(context) - 1)
		return ;
	i_context = (t_i_2d_context *)context;
	i_context->buffer[point.y * i_context->width + point.x]
		= (t_uint32)point.color;
}

void	put_2d_line(t_2d_context *context, t_2d_point a, t_2d_point b)
{
	t_printable_2d_line	setuped_line;

	setuped_line = setup_line(a, b);
	put_2d_point(context, setuped_line.current);
	while (setuped_line.current.x != b.x
		|| setuped_line.current.y != b.y)
	{
		setuped_line.e2 = 2 * setuped_line.err;
		if (setuped_line.e2 > -setuped_line.dy)
		{
			setuped_line.err -= setuped_line.dy;
			setuped_line.current.x += setuped_line.sx;
		}
		if (setuped_line.e2 < setuped_line.dx)
		{
			setuped_line.err += setuped_line.dx;
			setuped_line.current.y += setuped_line.sy;
		}
		if (a.color != b.color)
			setuped_line.current.color
				= get_gradian(a.color, b.color,
					setuped_line.line_len,
					get_length(a, setuped_line.current));
		put_2d_point(context, setuped_line.current);
	}
}

void	put_2d_triangle(t_2d_context *context, t_2d_triangle triangle)
{
	put_2d_line(context, triangle.p[0], triangle.p[1]);
	put_2d_line(context, triangle.p[1], triangle.p[2]);
	put_2d_line(context, triangle.p[2], triangle.p[0]);
}

void	put_2d_quad(t_2d_context *context, t_2d_quad quad)
{
	put_2d_line(context, quad.p[0], quad.p[1]);
	put_2d_line(context, quad.p[1], quad.p[2]);
	put_2d_line(context, quad.p[2], quad.p[3]);
	put_2d_line(context, quad.p[3], quad.p[0]);
}

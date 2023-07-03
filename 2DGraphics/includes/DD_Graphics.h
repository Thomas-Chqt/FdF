/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DD_Graphics.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 18:24:02 by tchoquet          #+#    #+#             */
/*   Updated: 2023/06/26 17:30:50 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DD_GRAPHICS_H
# define DD_GRAPHICS_H

# include <libft.h>

typedef struct s_2d_context		t_2d_context;

typedef struct s_2d_point		t_2d_point;
typedef struct s_2d_triangle	t_2d_triangle;
typedef struct s_2d_quad		t_2d_quad;

struct s_2d_point
{
	int		x;
	int		y;
	t_color	color;
};

struct s_2d_triangle
{
	t_2d_point	p[3];
};

struct s_2d_quad
{
	t_2d_point	p[4];
};

t_2d_context	*create_2d_context(void *pixels_buffer, t_uint32 width,
					t_uint32 height);
void			delete_2d_context(t_2d_context *context);

void			put_2d_point(t_2d_context *context, t_2d_point point);
void			put_2d_line(t_2d_context *context, t_2d_point a, t_2d_point b);
void			put_2d_triangle(t_2d_context *context, t_2d_triangle triangle);
void			put_2d_quad(t_2d_context *context, t_2d_quad quad);

t_uint32		get_2d_context_height(t_2d_context *context);
t_uint32		get_2d_context_width(t_2d_context *context);
t_uint32		get_length(t_2d_point a, t_2d_point b);

#endif // DD_GRAPHICS_H
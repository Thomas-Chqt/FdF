/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DD_Graphics_internal.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 19:21:28 by tchoquet          #+#    #+#             */
/*   Updated: 2023/06/26 16:05:05 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DD_GRAPHICS_INTERNAL_H
# define DD_GRAPHICS_INTERNAL_H

# ifdef MEMCHEK
#  include <memory_leak_detector.h>
# endif // MEMCHEK

# include <stdlib.h>
# include <math.h>

# include "DD_Graphics.h"

typedef struct s_i_2d_context
{
	t_uint32	*buffer;
	t_uint32	width;
	t_uint32	height;

}	t_i_2d_context;

typedef struct s_printable_2d_line
{
	t_2d_point	current;
	t_uint32	line_len;
	int			dx;
	int			dy;
	int			sx;
	int			sy;
	int			err;
	int			e2;
}	t_printable_2d_line;

#endif // DD_GRAPHICS_INTERNAL_H
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 01:59:21 by tchoquet          #+#    #+#             */
/*   Updated: 2023/06/30 19:17:28 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define USE_QUADRILATERAL

# ifdef MEMCHEK
#  include <memory_leak_detector.h>
# endif // MEMCHEK

# include <stdlib.h>

# include <libft.h>
# include <ft_printf.h>
# include <wrapped_mlx.h>
# include <DDD_Graphics.h>

# define WIDTH 1280
# define HEIGHT 720

# define UNKNOWN_ERROR -1111
# define NO_MAP -2222
# define READ_ERROR -3333

typedef struct s_setup_data	t_setup_data;

struct s_setup_data
{
	t_window		*window;
	t_3d_context	*context;
	t_3d_model		map_model;
	t_3d_object		*map;
	t_projection	proj;
	t_bool			clicked;
	int				src_x;
	int				src_y;
	t_vect_3d		src_rot;
	t_vect_3d		new_rot;
	t_bool			rotation;
};

void	main_loop(void *data);
void	free_setup_data(void *data);

int		print_error(int error_code);

void	escape_action(void *data);
void	make_iso(void *data);
void	make_ortho(void *data);
void	wheel_up(int x, int y, void *data);
void	wheel_down(int x, int y, void *data);
void	up(void *data);
void	down(void *data);
void	right(void *data);
void	left(void *data);
void	click(int x, int y, void *data);
void	move(int x, int y, void *data);
void	toggle_rot(void *data);

#endif // FDF_H
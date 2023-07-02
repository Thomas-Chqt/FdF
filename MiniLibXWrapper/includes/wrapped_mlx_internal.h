/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapped_mlx_internal.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 01:47:38 by tchoquet          #+#    #+#             */
/*   Updated: 2023/07/02 20:04:01 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRAPPED_MLX_INTERNAL_H
# define WRAPPED_MLX_INTERNAL_H

# ifdef MEMCHECK
#  include <memory_leak_detector.h>
# endif // MEMCHECK

# include <libft.h>
# include <stdlib.h>

# include "mlx.h"
# include "wrapped_mlx.h"

typedef struct s_key_event
{
	unsigned int		id;
	t_keyboard_code		key_code;
	unsigned char		triggers;
	void				(*func)(void*);
	void				*data;

}	t_key_event;

typedef struct s_mouse_event
{
	unsigned int		id;
	t_mouse_code		mouse_code;
	unsigned char		triggers;
	void				(*func)(int x, int y, void*);
	void				*data;

}	t_mouse_event;

typedef struct s_mouse_move_event
{
	unsigned int		id;
	void				(*func)(int x, int y, void*);
	void				*data;

}	t_mouse_move_event;

typedef enum e_mouse_move_trigger {
	ON_MOUSEMOVE	= 0b00010000,
}	t_mouse_move_trigger;

typedef struct s_window_event
{
	unsigned int		id;
	unsigned char		triggers;
	void				(*func)(void*);
	void				*data;

}	t_window_event;

typedef struct s_i_window
{
	void			*mlx;
	void			*mlx_window;
	unsigned int	render_width;
	unsigned int	render_height;
	void			*mlx_render_image;
	void			*pixels;
	void			*setup_data;
	void			(*clean_func)(void *);
	t_list			*key_event_list_head;
	t_list			*mouse_event_list_head;
	t_list			*mouse_move_event_list_head;
	t_list			*window_event_list_head;
	unsigned char	created_hooks;

}	t_i_window;

int		main_loop_func_wrapper(void *param);
void	delete_window_wrapper(void *data);
void	free_wrapper_mlx(void *ptr);

#endif // WRAPPED_MLX_INTERNAL_H
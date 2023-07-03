/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapped_mlx.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 18:13:52 by tchoquet          #+#    #+#             */
/*   Updated: 2023/06/30 18:25:19 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRAPPED_MLX_H
# define WRAPPED_MLX_H

typedef struct s_window	t_window;

typedef enum e_keyboard_code {
	esc_key		= 53,
	space_key	= 49,
	one_key		= 18,
	two_key		= 19,
	three_key	= 20,
	four_key	= 21,
	five_key	= 23,
	left_key	= 123,
	right_key	= 124,
	up_key		= 126,
	down_key	= 125,
	enter_key	= 36,
	r_key		= 15,
	plus_key	= 24,
	minus_key	= 27
}	t_keyboard_code;

typedef enum e_keyboard_trigger {
	ON_KEYDOWN		= 0b00000001,
	ON_KEYUP		= 0b00000010,
}	t_keyboard_trigger;

typedef enum e_mouse_code {
	l_click	= 1,
	r_click	= 2,
	m_click	= 3,
	w_down	= 4,
	w_up	= 5
}	t_mouse_code;

typedef enum e_mouse_trigger {
	ON_MOUSEDOWN	= 0b00000100,
	ON_MOUSEUP		= 0b00001000,
}	t_mouse_trigger;

typedef enum e_window_trigger {
	ON_EXPOSE		= 0b00100000,
	ON_DESTROY		= 0b01000000
}	t_window_trigger;

t_window		*create_window(const char *title, unsigned int width,
					unsigned int height);
t_window		*set_setup_data(t_window *window, void *setup_data,
					void (*free_setup_data)(void *));
void			*get_pixel_buffer(t_window *window);
void			start_main_loop(t_window *window, void (*loop_func)(void*));
void			delete_window(t_window *window, int return_code);

unsigned int	add_on_key_event(t_window *window, t_keyboard_code key_code,
					unsigned char triggers,
					void (*func)(void*), void *data);

unsigned int	add_on_mouse_event(t_window *window, t_mouse_code mouse_code,
					unsigned char triggers,
					void (*func)(int x, int y, void*), void *data);

unsigned int	add_on_mouse_move_event(t_window *window,
					void (*func)(int x, int y, void*), void *data);

unsigned int	add_on_window_event(t_window *window, unsigned char triggers,
					void (*func)(void*), void *data);

#endif

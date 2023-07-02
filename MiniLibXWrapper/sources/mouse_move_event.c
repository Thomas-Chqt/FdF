/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_move_event.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 22:41:22 by tchoquet          #+#    #+#             */
/*   Updated: 2023/06/26 15:50:35 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wrapped_mlx_internal.h"

static t_mouse_move_event	*new_mouse_move_event(t_i_window *window);
static int					mouse_move_hook_func(int x, int y, void *param);
static void					play_event(void *event, void *data);

unsigned int	add_on_mouse_move_event(t_window *window,
					void (*func)(int x, int y, void*), void *data)
{
	t_i_window			*i_window;
	t_mouse_move_event	*new_event;

	if (window == NULL || func == NULL)
		return (0);
	i_window = (t_i_window *)window;
	new_event = new_mouse_move_event(i_window);
	if (new_event == NULL)
		return (0);
	new_event->func = func;
	new_event->data = data;
	ft_lstadd_front(&(i_window->mouse_move_event_list_head),
		ft_lstnew((void *)new_event));
	if ((i_window->created_hooks & ON_MOUSEMOVE) != ON_MOUSEMOVE)
		mlx_hook(i_window->mlx_window, 6, 0, &mouse_move_hook_func,
			(void *)i_window);
	i_window->created_hooks = (i_window->created_hooks | ON_MOUSEMOVE);
	return (new_event->id);
}

static t_mouse_move_event	*new_mouse_move_event(t_i_window *window)
{
	t_mouse_move_event	*new_event;

	new_event = malloc(sizeof(t_mouse_move_event));
	if (new_event == NULL)
		return (NULL);
	if (window->mouse_move_event_list_head == NULL)
		new_event->id = 1;
	else
		new_event->id = ((t_mouse_move_event *)
				window->mouse_move_event_list_head->data)->id + 1;
	return (new_event);
}

static int	mouse_move_hook_func(int x, int y, void *param)
{
	t_i_window	*i_window;
	void		*datas[2];

	i_window = (t_i_window *)param;
	datas[0] = ((void *)(&x));
	datas[1] = ((void *)(&y));
	lstiter_data(i_window->mouse_move_event_list_head, &play_event, datas);
	return (0);
}

static void	play_event(void *event, void *data)
{
	t_mouse_move_event	*mouse_move_event;

	mouse_move_event = (t_mouse_move_event *)event;
	mouse_move_event->func(*((int *)(((void **)data)[0])),
		*((int *)(((void **)data)[1])), mouse_move_event->data);
}

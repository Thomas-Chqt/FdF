/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 21:23:55 by tchoquet          #+#    #+#             */
/*   Updated: 2023/06/26 15:54:05 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wrapped_mlx_internal.h"

static t_mouse_event	*new_mouse_event(t_i_window *window);
static int				mouse_down_hook_func(int button, int x, int y,
							void *param);
static int				mouse_up_hook_func(int button, int x, int y,
							void *param);
static void				play_event(void *event, void *data);

unsigned int	add_on_mouse_event(t_window *window, t_mouse_code mouse_code,
					unsigned char triggers,
					void (*func)(int x, int y, void*), void *data)
{
	t_i_window		*i_window;
	t_mouse_event	*new_event;

	if (window == NULL || mouse_code == 0 || triggers == 0 || func == NULL)
		return (0);
	i_window = (t_i_window *)window;
	new_event = new_mouse_event(i_window);
	if (new_event == NULL)
		return (0);
	new_event->mouse_code = mouse_code;
	new_event->triggers = triggers;
	new_event->func = func;
	new_event->data = data;
	ft_lstadd_front(&(i_window->mouse_event_list_head),
		ft_lstnew((void *)new_event));
	if (((triggers & ON_MOUSEDOWN) == ON_MOUSEDOWN)
		&& ((i_window->created_hooks & ON_MOUSEDOWN) != ON_MOUSEDOWN))
		mlx_hook(i_window->mlx_window, 4, 0,
			&mouse_down_hook_func, (void *)i_window);
	if (((triggers & ON_MOUSEUP) == ON_MOUSEUP)
		&& ((i_window->created_hooks & ON_MOUSEUP) != ON_MOUSEUP))
		mlx_hook(i_window->mlx_window, 5, 0,
			&mouse_up_hook_func, (void *)i_window);
	i_window->created_hooks = (i_window->created_hooks | triggers);
	return (new_event->id);
}

static t_mouse_event	*new_mouse_event(t_i_window *window)
{
	t_mouse_event	*new_event;

	new_event = malloc(sizeof(t_mouse_event));
	if (new_event == NULL)
		return (NULL);
	if (window->mouse_event_list_head == NULL)
		new_event->id = 1;
	else
		new_event->id = ((t_mouse_event *)
				window->mouse_event_list_head->data)->id + 1;
	return (new_event);
}

static int	mouse_down_hook_func(int button, int x, int y, void *param)
{
	t_i_window				*i_window;
	static t_mouse_trigger	trigger = ON_MOUSEDOWN;
	void					*datas[4];

	i_window = (t_i_window *)param;
	datas[0] = ((void *)(&button));
	datas[1] = ((void *)(&trigger));
	datas[2] = ((void *)(&x));
	datas[3] = ((void *)(&y));
	lstiter_data(i_window->mouse_event_list_head, &play_event, datas);
	return (0);
}

static int	mouse_up_hook_func(int button, int x, int y, void *param)
{
	t_i_window				*i_window;
	static t_mouse_trigger	trigger = ON_MOUSEUP;
	void					*datas[4];

	i_window = (t_i_window *)param;
	datas[0] = ((void *)(&button));
	datas[1] = ((void *)(&trigger));
	datas[2] = ((void *)(&x));
	datas[3] = ((void *)(&y));
	lstiter_data(i_window->mouse_event_list_head, &play_event, datas);
	return (0);
}

static void	play_event(void *event, void *data)
{
	t_mouse_event	*mouse_event;
	t_mouse_code	mouse_code;
	t_mouse_trigger	trigger;

	mouse_event = (t_mouse_event *)event;
	mouse_code = *((t_mouse_code *)(((void **)data)[0]));
	trigger = *((t_mouse_trigger *)(((void **)data)[1]));
	if (mouse_event->mouse_code != mouse_code)
		return ;
	if ((mouse_event->triggers & trigger) != trigger)
		return ;
	mouse_event->func(*((int *)(((void **)data)[2])),
		*((int *)(((void **)data)[3])), mouse_event->data);
}

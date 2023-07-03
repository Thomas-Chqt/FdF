/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   on_window_event.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 01:16:52 by tchoquet          #+#    #+#             */
/*   Updated: 2023/06/26 15:48:02 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wrapped_mlx_internal.h"

static t_window_event	*new_window_event(t_i_window *window);
static int				expose_hook_func(void *param);
static int				destroy_hook_func(void *param);
static void				play_event(void *event, void *data);

unsigned int	add_on_window_event(t_window *window, unsigned char triggers,
					void (*func)(void*), void *data)
{
	t_i_window		*i_window;
	t_window_event	*new_event;

	if (window == NULL || triggers == 0 || func == NULL)
		return (0);
	i_window = (t_i_window *)window;
	new_event = new_window_event(i_window);
	if (new_event == NULL)
		return (0);
	new_event->triggers = triggers;
	new_event->func = func;
	new_event->data = data;
	ft_lstadd_front(&(i_window->window_event_list_head),
		ft_lstnew((void *)new_event));
	if (((triggers & ON_EXPOSE) == ON_EXPOSE)
		&& ((i_window->created_hooks & ON_EXPOSE) != ON_EXPOSE))
		mlx_hook(i_window->mlx_window, 12, 0,
			&expose_hook_func, (void *)i_window);
	if (((triggers & ON_DESTROY) == ON_DESTROY)
		&& ((i_window->created_hooks & ON_DESTROY) != ON_DESTROY))
		mlx_hook(i_window->mlx_window, 17, 0,
			&destroy_hook_func, (void *)i_window);
	i_window->created_hooks = (i_window->created_hooks | triggers);
	return (new_event->id);
}

static t_window_event	*new_window_event(t_i_window *window)
{
	t_window_event	*new_event;

	new_event = malloc(sizeof(t_window_event));
	if (new_event == NULL)
		return (NULL);
	if (window->window_event_list_head == NULL)
		new_event->id = 1;
	else
		new_event->id
			= ((t_window_event *)window->window_event_list_head->data)->id + 1;
	return (new_event);
}

static int	expose_hook_func(void *param)
{
	t_i_window				*i_window;
	static t_window_trigger	trigger = ON_EXPOSE;

	i_window = (t_i_window *)param;
	lstiter_data(i_window->window_event_list_head, &play_event, &trigger);
	return (0);
}

static int	destroy_hook_func(void *param)
{
	t_i_window				*i_window;
	static t_window_trigger	trigger = ON_DESTROY;

	i_window = (t_i_window *)param;
	lstiter_data(i_window->window_event_list_head, &play_event, &trigger);
	return (0);
}

static void	play_event(void *event, void *data)
{
	t_window_event		*window_event;
	t_window_trigger	trigger;

	window_event = (t_window_event *)event;
	trigger = *((t_window_trigger *)data);
	if ((window_event->triggers & trigger) != trigger)
		return ;
	window_event->func(window_event->data);
}

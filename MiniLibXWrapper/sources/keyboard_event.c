/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_event.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 17:57:22 by tchoquet          #+#    #+#             */
/*   Updated: 2023/06/26 15:52:57 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wrapped_mlx_internal.h"

static t_key_event	*new_key_event(t_i_window *window);
static int			key_down_hook_func(int keycode, void *param);
static int			key_up_hook_func(int keycode, void *param);
static void			play_event(void *event, void *data);

unsigned int	add_on_key_event(t_window *window, t_keyboard_code key_code,
					unsigned char triggers,
					void (*func)(void*), void *data)
{
	t_i_window	*i_window;
	t_key_event	*new_event;

	if (window == NULL || key_code == 0 || triggers == 0 || func == NULL)
		return (0);
	i_window = (t_i_window *)window;
	new_event = new_key_event(i_window);
	if (new_event == NULL)
		return (0);
	new_event->key_code = key_code;
	new_event->triggers = triggers;
	new_event->func = func;
	new_event->data = data;
	ft_lstadd_front(&(i_window->key_event_list_head),
		ft_lstnew((void *)new_event));
	if (((triggers & ON_KEYDOWN) == ON_KEYDOWN)
		&& ((i_window->created_hooks & ON_KEYDOWN) != ON_KEYDOWN))
		mlx_hook(i_window->mlx_window, 2, 0,
			&key_down_hook_func, (void *)i_window);
	if (((triggers & ON_KEYUP) == ON_KEYUP)
		&& ((i_window->created_hooks & ON_KEYUP) != ON_KEYUP))
		mlx_hook(i_window->mlx_window, 3, 0,
			&key_up_hook_func, (void *)i_window);
	i_window->created_hooks = (i_window->created_hooks | triggers);
	return (new_event->id);
}

static t_key_event	*new_key_event(t_i_window *window)
{
	t_key_event	*new_event;

	new_event = malloc(sizeof(t_key_event));
	if (new_event == NULL)
		return (NULL);
	if (window->key_event_list_head == NULL)
		new_event->id = 1;
	else
		new_event->id
			= ((t_key_event *)window->key_event_list_head->data)->id + 1;
	return (new_event);
}

static int	key_down_hook_func(int keycode, void *param)
{
	t_i_window					*i_window;
	static t_keyboard_trigger	trigger = ON_KEYDOWN;
	void						*datas[2];

	i_window = (t_i_window *)param;
	datas[0] = ((void *)(&keycode));
	datas[1] = ((void *)(&trigger));
	lstiter_data(i_window->key_event_list_head, &play_event, datas);
	return (0);
}

static int	key_up_hook_func(int keycode, void *param)
{
	t_i_window					*i_window;
	static t_keyboard_trigger	trigger = ON_KEYUP;
	void						*datas[2];

	i_window = (t_i_window *)param;
	datas[0] = ((void *)(&keycode));
	datas[1] = ((void *)(&trigger));
	lstiter_data(i_window->key_event_list_head, &play_event, datas);
	return (0);
}

static void	play_event(void *event, void *data)
{
	t_key_event			*key_event;
	t_keyboard_code		keycode;
	t_keyboard_trigger	trigger;

	key_event = (t_key_event *)event;
	keycode = *((t_keyboard_code *)(((void **)data)[0]));
	trigger = *((t_keyboard_trigger *)(((void **)data)[1]));
	if (key_event->key_code != keycode)
		return ;
	if ((key_event->triggers & trigger) != trigger)
		return ;
	key_event->func(key_event->data);
}

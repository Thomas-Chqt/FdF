/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapped_mlx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 13:23:38 by tchoquet          #+#    #+#             */
/*   Updated: 2023/06/26 15:47:05 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wrapped_mlx_internal.h"

t_window	*create_window(const char *title, unsigned int width,
				unsigned int height)
{
	static t_i_window	new_window;

	if (title == NULL || width < 10 || height < 10)
		return (NULL);
	new_window.mlx = mlx_init();
	if (new_window.mlx == NULL)
		return (NULL);
	new_window.mlx_window = mlx_new_window(new_window.mlx, width, height,
			(char *)title);
	if (new_window.mlx_window == NULL)
		return (NULL);
	new_window.render_width = width;
	new_window.render_height = height;
	add_on_window_event(((t_window *)(&new_window)), ON_DESTROY,
		&delete_window_wrapper, (t_window *)(&new_window));
	return ((t_window *)(&new_window));
}

t_window	*set_setup_data(t_window *window, void *setup_data,
				void (*free_setup_data)(void *))
{
	t_i_window	*i_window;

	if (window == NULL)
		return (NULL);
	i_window = (t_i_window *)window;
	i_window->setup_data = setup_data;
	i_window->clean_func = free_setup_data;
	return (window);
}

void	*get_pixel_buffer(t_window *window)
{
	t_i_window	*i_window;
	int			bits_per_pixel;
	int			size_line;
	int			endian;

	if (window == NULL)
		return (NULL);
	i_window = (t_i_window *)window;
	if (i_window->pixels != NULL)
		return (i_window->pixels);
	i_window->mlx_render_image = mlx_new_image(i_window->mlx,
			i_window->render_width, i_window->render_width);
	if (i_window->mlx_render_image == NULL)
		return (NULL);
	i_window->pixels = mlx_get_data_addr(i_window->mlx_render_image,
			&bits_per_pixel, &size_line, &endian);
	return (i_window->pixels);
}

void	start_main_loop(t_window *window, void (*loop_func)(void*))
{
	t_i_window	*i_window;
	void		*args[2];

	if (window == NULL || loop_func == NULL)
		return ;
	i_window = (t_i_window *)window;
	args[0] = i_window;
	args[1] = loop_func;
	mlx_loop_hook(i_window->mlx, &main_loop_func_wrapper, args);
	mlx_loop(i_window->mlx);
}

void	delete_window(t_window *window, int return_code)
{
	t_i_window	*i_window;

	if (window == NULL)
		return ;
	i_window = (t_i_window *)window;
	if (i_window->clean_func != NULL)
		i_window->clean_func(i_window->setup_data);
	ft_lstclear(&(i_window->key_event_list_head), &free);
	ft_lstclear(&(i_window->mouse_event_list_head), &free);
	ft_lstclear(&(i_window->mouse_move_event_list_head), &free);
	ft_lstclear(&(i_window->window_event_list_head), &free);
	if (i_window->mlx_render_image)
		mlx_destroy_image(i_window->mlx, i_window->mlx_render_image);
	if (i_window->mlx_window)
		mlx_destroy_window(i_window->mlx, i_window->mlx_window);
	exit(return_code);
}

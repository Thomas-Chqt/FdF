/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrappers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:17:26 by tchoquet          #+#    #+#             */
/*   Updated: 2023/06/26 15:46:04 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wrapped_mlx_internal.h"

int	main_loop_func_wrapper(void *param)
{
	void		**args;
	t_i_window	*i_window;
	void		(*loop_func)(void *data);

	if (param == NULL)
		return (-1);
	args = (void **)param;
	i_window = (t_i_window *)(args[0]);
	loop_func = args[1];
	if (i_window->mlx_render_image != NULL)
		ft_bzero(i_window->pixels, i_window->render_height
			* i_window->render_width * 4);
	loop_func(i_window->setup_data);
	if (i_window->mlx_render_image != NULL)
		mlx_put_image_to_window(i_window->mlx, i_window->mlx_window,
			i_window->mlx_render_image, 0, 0);
	return (0);
}

void	delete_window_wrapper(void *data)
{
	delete_window((t_window *)data, 0);
}

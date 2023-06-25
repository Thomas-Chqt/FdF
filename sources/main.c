/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 02:01:01 by tchoquet          #+#    #+#             */
/*   Updated: 2023/06/25 19:29:19 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#ifdef MEMCHEK

__attribute__((destructor))
static void	destructor(void)
{
	print_report();
}

#endif // MEMCHEK

int	main(int argc, char const *argv[])
{
	t_window		*window;
	t_setup_data	*setup_data;

	window = create_window("FdF", WIDTH, HEIGHT);
	setup_data = init_setup_data(window, argc, argv);
	if (setup_data == NULL)
	{
		print_error(errno);
		delete_window(window, errno);
	}
	swich_to_iso(NULL, setup_data);
	add_on_key_event(window, one_key, ON_KEYUP, &toggle_rotation, setup_data);
	start_main_loop(window, &main_loop, setup_data, &free_setup_data);
	return (0);
}

void	main_loop(t_window *window, void *data)
{
	t_setup_data	*setup_data;

	window = NULL;
	setup_data = (t_setup_data *)data;
	if (setup_data->rotation == true)
		rotate_object(setup_data->map, new_vect_3d(0, 0.1, 0));
	render_3d_scene(setup_data->scene);
}

void	free_setup_data(void *data)
{
	free(((t_setup_data *)data)->original_model.polygones);
	delete_3d_context(((t_setup_data *)data)->ddd_context);
	free_arguments(((t_setup_data *)data)->arguments);
}

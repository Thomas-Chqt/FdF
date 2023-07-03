/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 02:01:01 by tchoquet          #+#    #+#             */
/*   Updated: 2023/07/02 19:59:38 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#ifdef MEMCHECK

__attribute__((destructor))
static void	destructor(void)
{
	print_report();
}

#endif // MEMCHECK

static void	add_envents(t_window *window, void *data)
{
	add_on_key_event(window, esc_key, ON_KEYUP, &escape_action, data);
	add_on_key_event(window, one_key, ON_KEYUP, &make_iso, data);
	add_on_key_event(window, two_key, ON_KEYUP, &make_ortho, data);
	add_on_mouse_event(window, w_up, ON_MOUSEDOWN, &wheel_up, data);
	add_on_mouse_event(window, w_down, ON_MOUSEDOWN, &wheel_down, data);
	add_on_key_event(window, up_key, ON_KEYUP, &up, data);
	add_on_key_event(window, down_key, ON_KEYUP, &down, data);
	add_on_key_event(window, right_key, ON_KEYUP, &right, data);
	add_on_key_event(window, left_key, ON_KEYUP, &left, data);
	add_on_mouse_event(window, l_click, ON_MOUSEDOWN | ON_MOUSEUP,
		&click, data);
	add_on_mouse_move_event(window, &move, data);
	add_on_key_event(window, r_key, ON_KEYUP, &toggle_rot, data);
}

int	main(int argc, char const *argv[])
{
	t_setup_data	setup_data;

	setup_data = (t_setup_data){0};
	if (argc < 2)
		return (print_error(NO_MAP));
	setup_data.window = set_setup_data(create_window("FdF", WIDTH, HEIGHT),
			&setup_data, &free_setup_data);
	if (setup_data.window == NULL)
		return (print_error(UNKNOWN_ERROR));
	add_envents(setup_data.window, &setup_data);
	setup_data.context = create_3d_context(get_pixel_buffer(setup_data.window),
			WIDTH, HEIGHT);
	if (setup_data.context == NULL)
		delete_window(setup_data.window, print_error(UNKNOWN_ERROR));
	setup_data.map_model = load_file(argv[1]);
	if (setup_data.map_model.quads == NULL)
		delete_window(setup_data.window, print_error(READ_ERROR));
	make_iso((void *)&setup_data);
	start_main_loop(setup_data.window, &main_loop);
	return (0);
}

void	main_loop(void *data)
{
	t_setup_data	*setup_data;

	setup_data = (t_setup_data *)data;
	if (setup_data->rotation == true && setup_data->proj == isometric)
		set_3d_object_rotation(setup_data->map,
			vector_add(get_3d_object_rotation(setup_data->map),
				new_vect_3d(0, 0.1, 0)));
	if (setup_data->rotation == true && setup_data->proj == orthographic)
		set_3d_object_rotation(setup_data->map,
			vector_add(get_3d_object_rotation(setup_data->map),
				new_vect_3d(0, 0, 0.1)));
	render_3d_scene(get_3d_scene(setup_data->context, 0));
}

void	free_setup_data(void *data)
{
	t_setup_data	*setup_data;

	setup_data = (t_setup_data *)data;
	free(setup_data->map_model.quads);
	delete_3d_context(setup_data->context);
}

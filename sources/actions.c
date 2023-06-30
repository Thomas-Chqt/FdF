/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 17:19:05 by tchoquet          #+#    #+#             */
/*   Updated: 2023/06/30 19:10:50 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	escape_action(void *data)
{
	t_setup_data	*setup_data;

	setup_data = (t_setup_data *)data;
	delete_window(setup_data->window, 0);
}

void	make_iso(void *data)
{
	t_setup_data	*setup_data;
	t_vect_3d		size;
	float			scale_fact;

	setup_data = (t_setup_data *)data;
	change_projection(get_3d_scene(setup_data->context, isometric), isometric);
	setup_data->proj = isometric;
	size = get_projected_size(setup_data->context, setup_data->map_model,
			isometric);
	scale_fact = (WIDTH - 1) / size.x;
	if (size.y * scale_fact > HEIGHT)
		scale_fact = (HEIGHT - 1) / size.y;
	scale_3d_model(&setup_data->map_model, new_vect_3d(scale_fact, scale_fact,
			scale_fact));
	clear_3d_scene(get_3d_scene(setup_data->context, isometric));
	setup_data->map = create_3d_object(setup_data->map_model);
	add_3d_object_to_scene(setup_data->map, get_3d_scene(setup_data->context,
			isometric));
}

void	make_ortho(void *data)
{
	t_setup_data	*setup_data;
	t_vect_3d		size;
	float			scale_fact;

	setup_data = (t_setup_data *)data;
	change_projection(get_3d_scene(setup_data->context, orthographic),
		orthographic);
	setup_data->proj = orthographic;
	size = get_projected_size(setup_data->context, setup_data->map_model,
			orthographic);
	scale_fact = (WIDTH - 1) / size.x;
	if (size.z * scale_fact > HEIGHT)
		scale_fact = (HEIGHT - 1) / size.z;
	scale_3d_model(&setup_data->map_model, new_vect_3d(scale_fact,
			scale_fact, scale_fact));
	clear_3d_scene(get_3d_scene(setup_data->context, orthographic));
	setup_data->map = create_3d_object(setup_data->map_model);
	set_3d_object_rotation(setup_data->map, new_vect_3d(-90, 0, 0));
	add_3d_object_to_scene(setup_data->map, get_3d_scene(setup_data->context,
			orthographic));
}

void	wheel_up(int x, int y, void *data)
{
	t_setup_data	*setup_data;

	x = 0;
	y = 0;
	setup_data = (t_setup_data *)data;
	set_3d_object_scale(setup_data->map,
		vector_add(get_3d_object_scale(setup_data->map),
			new_vect_3d(0.1, 0.1, 0.1))
		);
}

void	wheel_down(int x, int y, void *data)
{
	t_setup_data	*setup_data;

	x = 0;
	y = 0;
	setup_data = (t_setup_data *)data;
	set_3d_object_scale(setup_data->map,
		vector_add(get_3d_object_scale(setup_data->map),
			new_vect_3d(-0.1, -0.1, -0.1))
		);
}

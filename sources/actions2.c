/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 18:27:22 by tchoquet          #+#    #+#             */
/*   Updated: 2023/06/30 18:34:30 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	up(void *data)
{
	t_setup_data	*setup_data;

	setup_data = (t_setup_data *)data;
	if (setup_data->proj == isometric)
	{
		set_3d_object_position(setup_data->map,
			vector_add(get_3d_object_position(setup_data->map),
				new_vect_3d(0, 0, 0.1)));
	}
	else
	{
		set_3d_object_position(setup_data->map,
			vector_add(get_3d_object_position(setup_data->map),
				new_vect_3d(0, 0.1, 0)));
	}
}

void	down(void *data)
{
	t_setup_data	*setup_data;

	setup_data = (t_setup_data *)data;
	if (setup_data->proj == isometric)
	{
		set_3d_object_position(setup_data->map,
			vector_add(get_3d_object_position(setup_data->map),
				new_vect_3d(0, 0, -0.1)));
	}
	else
	{
		set_3d_object_position(setup_data->map,
			vector_add(get_3d_object_position(setup_data->map),
				new_vect_3d(0, -0.1, 0)));
	}
}

void	right(void *data)
{
	t_setup_data	*setup_data;

	setup_data = (t_setup_data *)data;
	set_3d_object_position(setup_data->map,
		vector_add(get_3d_object_position(setup_data->map),
			new_vect_3d(0.1, 0, 0)));
}

void	left(void *data)
{
	t_setup_data	*setup_data;

	setup_data = (t_setup_data *)data;
	set_3d_object_position(setup_data->map,
		vector_add(get_3d_object_position(setup_data->map),
			new_vect_3d(-0.1, 0, 0)));
}

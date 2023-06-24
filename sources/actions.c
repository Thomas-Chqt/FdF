/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 18:23:48 by tchoquet          #+#    #+#             */
/*   Updated: 2023/06/24 20:05:45 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	swich_to_iso(t_window *window, void *data)
{	
	t_setup_data	*setup_data;
	t_3d_model		new_model;
	float			model_h;
	t_uint32		fv[2];

	window = NULL;
	setup_data = (t_setup_data *)data;
	new_model.poly_count = setup_data->original_model.poly_count;
	new_model.polygones = malloc(sizeof(t_3d_polygone) * new_model.poly_count);
	model_h = get_height_iso(setup_data->original_model);
	if (new_model.polygones == NULL || model_h < 0)
		exit_error(UNKNOWN_ERROR, &free_setup_data, data);
	fv[0] = -1;
	while (++(fv[0]) < new_model.poly_count)
	{
		new_model.polygones[fv[0]] = setup_data->original_model.polygones[*fv];
		fv[1] = -1;
		while (++(fv[1]) < 4)
			new_model.polygones[fv[0]].p[fv[1]].pos = vector_mult(new_model
					.polygones[fv[0]].p[fv[1]].pos, (2.0f / model_h));
	}
	center_3d_model(&new_model);
	clear_3d_scene(setup_data->scene);
	setup_data->map = create_3d_object(new_model);
	add_3d_object_to_scene(setup_data->map, setup_data->scene);
}

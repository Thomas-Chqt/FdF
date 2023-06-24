/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 01:59:33 by tchoquet          #+#    #+#             */
/*   Updated: 2023/06/24 19:47:02 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_mat4x4	get_rot_x_mat(float angle);
static t_mat4x4	get_rot_y_mat(float angle);

t_setup_data	*init_setup_data(int argc, char const *argv[])
{
	static t_setup_data	setup_data;

	setup_data.arguments = parse_arguments(argc, argv);
	if (setup_data.arguments == NULL)
		exit_error(0, &free_setup_data, &setup_data);
	setup_data.window = create_window("FdF", WIDTH, HEIGHT);
	if (setup_data.window == NULL )
		exit_error(UNKNOWN_ERROR, &free_setup_data, &setup_data);
	setup_data.ddd_context = create_3d_context(
			get_pixel_buffer(setup_data.window), WIDTH, HEIGHT, false);
	if (setup_data.ddd_context == NULL)
		exit_error(UNKNOWN_ERROR, &free_setup_data, &setup_data);
	setup_data.scene = get_3d_scene(setup_data.ddd_context, isometric);
	if (setup_data.scene == NULL)
		exit_error(UNKNOWN_ERROR, &free_setup_data, &setup_data);
	setup_data.original_model = load_file(setup_data.arguments->map_file);
	if (setup_data.original_model.poly_count == 0)
		exit_error(MAP_READ_ERROR, &free_setup_data, &setup_data);
	return (&setup_data);
}

void	free_setup_data(void *data)
{
	free(((t_setup_data *)data)->original_model.polygones);
	delete_3d_context(((t_setup_data *)data)->ddd_context);
	delete_window(((t_setup_data *)data)->window);
	free_arguments(((t_setup_data *)data)->arguments);
}

float	get_height_iso(t_3d_model model)
{
	t_3d_model	temp_model;
	t_uint32	f;
	t_uint32	v;
	float		height;

	temp_model.polygones = ft_calloc(model.poly_count, sizeof(t_3d_polygone));
	if (temp_model.polygones == NULL)
		return (-1);
	temp_model.poly_count = model.poly_count;
	f = -1;
	while (++f < model.poly_count)
	{
		temp_model.polygones[f] = model.polygones[f];
		v = -1;
		while (++v < 4)
		{
			temp_model.polygones[f].p[v].pos = vect_x_mat(temp_model
					.polygones[f].p[v].pos, get_rot_y_mat(45));
			temp_model.polygones[f].p[v].pos = vect_x_mat(temp_model
					.polygones[f].p[v].pos, get_rot_x_mat(-35.264));
		}
	}
	height = get_3d_model_size(temp_model).y;
	free(temp_model.polygones);
	return (height);
}

static t_mat4x4	get_rot_x_mat(float angle)
{
	t_mat4x4	mat;

	mat = identity_matrix();
	mat.m[1][1] = cosf(angle * M_PI / 180);
	mat.m[1][2] = sinf(angle * M_PI / 180);
	mat.m[2][1] = -sinf(angle * M_PI / 180);
	mat.m[2][2] = cosf(angle * M_PI / 180);
	return (mat);
}

static t_mat4x4	get_rot_y_mat(float angle)
{
	t_mat4x4	mat;

	mat = identity_matrix();
	mat.m[0][0] = cosf(angle * M_PI / 180);
	mat.m[0][2] = -sinf(angle * M_PI / 180);
	mat.m[2][0] = sinf(angle * M_PI / 180);
	mat.m[2][2] = cosf(angle * M_PI / 180);
	return (mat);
}

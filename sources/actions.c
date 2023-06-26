/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 18:23:48 by tchoquet          #+#    #+#             */
/*   Updated: 2023/06/26 12:50:29 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static float	get_height_iso(t_3d_model model);
static t_mat4x4	get_rot_x_mat(float angle);
static t_mat4x4	get_rot_y_mat(float angle);
static void		exit_error(t_window *window, t_setup_data *setup_data,
					int error_code, t_3d_polygone *polys);
static void		create_new_obj(t_setup_data *setup_data, t_3d_model model);

void	swich_to_iso(t_window *window, void *data)
{	
	t_setup_data	*setup_data;
	t_3d_model		new_model;
	float			model_h;
	t_uint32		f;
	t_uint32		v;

	window = NULL;
	setup_data = (t_setup_data *)data;
	new_model.poly_count = setup_data->original_model.poly_count;
	new_model.polygones = malloc(sizeof(t_3d_polygone) * new_model.poly_count);
	if (new_model.polygones == NULL)
		exit_error(window, setup_data, UNKNOWN_ERROR, NULL);
	model_h = get_height_iso(setup_data->original_model);
	if (model_h < 0)
		exit_error(window, setup_data, UNKNOWN_ERROR, NULL);
	f = -1;
	while (++f < new_model.poly_count)
	{
		new_model.polygones[f] = setup_data->original_model.polygones[f];
		v = -1;
		while (++v < 4)
			new_model.polygones[f].p[v].pos = vector_mult(new_model
					.polygones[f].p[v].pos, (2.0f / model_h));
	}
	create_new_obj(setup_data, new_model);
}

void	toggle_rotation(t_window *window, void *data)
{
	t_setup_data	*setup_data;

	window = NULL;
	setup_data = (t_setup_data *)data;
	if (setup_data->rotation == false)
		setup_data->rotation = true;
	else
		setup_data->rotation = false;
}

static float	get_height_iso(t_3d_model model)
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

static void	exit_error(t_window *window, t_setup_data *setup_data,
				int error_code, t_3d_polygone *polys)
{
	free(polys);
	print_error(error_code);
	free_setup_data(setup_data);
	delete_window(window, error_code);
}

static void	create_new_obj(t_setup_data *setup_data, t_3d_model model)
{
	center_3d_model(&model);
	clear_3d_scene(setup_data->scene);
	setup_data->map = create_3d_object(model);
	add_3d_object_to_scene(setup_data->map, setup_data->scene);
}

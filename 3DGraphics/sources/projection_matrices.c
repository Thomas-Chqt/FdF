/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_matrices.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 16:48:23 by tchoquet          #+#    #+#             */
/*   Updated: 2023/06/30 16:29:29 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DDD_Graphics_internal.h"

static t_mat4x4	get_perspective_proj_matrix(t_2d_context *dd_context);
static t_mat4x4	get_isometric_proj_matrix(t_2d_context *dd_context);
static t_mat4x4	get_orthographic_proj_matrix(t_2d_context *dd_context);

t_mat4x4	get_projection_matrix(t_2d_context *dd_context,
				t_projection proj_type)
{
	if (proj_type == orthographic)
		return (get_orthographic_proj_matrix(dd_context));
	if (proj_type == isometric)
		return (get_isometric_proj_matrix(dd_context));
	if (proj_type == perspective)
		return (get_perspective_proj_matrix(dd_context));
	return (identity_matrix());
}

static t_mat4x4	get_orthographic_proj_matrix(t_2d_context *dd_context)
{
	t_mat4x4	proj_mat;
	float		f_aspect_ratio;

	f_aspect_ratio = (float)get_2d_context_height(dd_context)
		/ (float)get_2d_context_width(dd_context);
	proj_mat = identity_matrix();
	proj_mat.m[0][0] = f_aspect_ratio;
	return (proj_mat);
}

static t_mat4x4	get_isometric_proj_matrix(t_2d_context *dd_context)
{
	return (mat_x_mat(mat_x_mat(rota_y_mat(45), rota_x_mat(-35.264)),
			get_orthographic_proj_matrix(dd_context)));
}

static t_mat4x4	get_perspective_proj_matrix(t_2d_context *dd_context)
{
	t_mat4x4	matrix;
	float		f_fov_rad;
	float		f_aspect_ratio;

	f_fov_rad = 1.0f / tanf(FOV * 0.5f / 180.0f * 3.14159f);
	f_aspect_ratio = (float)get_2d_context_height(dd_context)
		/ (float)get_2d_context_width(dd_context);
	matrix = (t_mat4x4){};
	matrix.m[0][0] = f_aspect_ratio * f_fov_rad;
	matrix.m[1][1] = f_fov_rad;
	matrix.m[2][2] = F_FAR / (F_FAR - F_NEAR);
	matrix.m[3][2] = (-F_FAR * F_NEAR) / (F_FAR - F_NEAR);
	matrix.m[2][3] = 1.0f;
	matrix.m[3][3] = 0.0f;
	return (matrix);
}

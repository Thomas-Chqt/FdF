/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 17:47:06 by tchoquet          #+#    #+#             */
/*   Updated: 2023/06/30 16:07:55 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DDD_Graphics_internal.h"

void	rotate_3d_model(t_3d_model *model, t_vect_3d angles)
{
	t_mat4x4	mat;
	t_uint32	f;

	mat = rotation_matrix(angles);
	f = 0;
	while (f < model->quad_count)
	{
		model->quads[f].p[0].pos = vect_x_mat(model->quads[f].p[0].pos, mat);
		model->quads[f].p[1].pos = vect_x_mat(model->quads[f].p[1].pos, mat);
		model->quads[f].p[2].pos = vect_x_mat(model->quads[f].p[2].pos, mat);
		model->quads[f].p[3].pos = vect_x_mat(model->quads[f].p[3].pos, mat);
		f++;
	}	
}

t_vect_3d	get_3d_object_rotation(t_3d_object *object)
{
	if (object == NULL)
		return (new_vect_3d(-1, -1, -1));
	return (((t_i_3d_object *)object)->rotation);
}

void	set_3d_object_rotation(t_3d_object *object, t_vect_3d rotation)
{
	if (object == NULL)
		return ;
	if (rotation.x < -360)
		rotation.x += 360;
	if (rotation.x > 360)
		rotation.x -= 360;
	if (rotation.y < -360)
		rotation.y += 360;
	if (rotation.y > 360)
		rotation.y -= 360;
	if (rotation.z < -360)
		rotation.z += 360;
	if (rotation.z > 360)
		rotation.z -= 360;
	if (rotation.x < 0)
		rotation.x = 360 + rotation.x;
	if (rotation.y < 0)
		rotation.y = 360 + rotation.y;
	if (rotation.z < 0)
		rotation.z = 360 + rotation.z;
	((t_i_3d_object *)object)->rotation = rotation;
	refresh_mesh((t_i_3d_object *)object);
}

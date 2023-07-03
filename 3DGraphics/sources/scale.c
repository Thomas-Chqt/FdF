/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 18:01:36 by tchoquet          #+#    #+#             */
/*   Updated: 2023/06/30 16:28:04 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DDD_Graphics_internal.h"

void	scale_3d_model(t_3d_model *model, t_vect_3d scales)
{
	t_mat4x4	mat;
	t_uint32	f;

	mat = scale_matrix(scales);
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

t_vect_3d	get_3d_object_scale(t_3d_object *object)
{
	if (object == NULL)
		return (new_vect_3d(-1, -1, -1));
	return (((t_i_3d_object *)object)->scale);
}

void	set_3d_object_scale(t_3d_object *object, t_vect_3d scale)
{
	if (object == NULL)
		return ;
	if (scale.x < 0)
		scale.x = 0;
	if (scale.y < 0)
		scale.y = 0;
	if (scale.z < 0)
		scale.z = 0;
	((t_i_3d_object *)object)->scale = scale;
	refresh_mesh((t_i_3d_object *)object);
}

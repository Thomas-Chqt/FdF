/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 18:21:24 by tchoquet          #+#    #+#             */
/*   Updated: 2023/06/30 16:34:07 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DDD_Graphics_internal.h"

static void	put_3d_object(void *object, void *scene);

void	put_3d_model(t_3d_context *context, t_3d_model model,
			t_projection proj_type)
{
	t_i_3d_context	*i_context;
	t_mat4x4		proj_mat;
	t_uint32		i;

	if (context == NULL)
		return ;
	i_context = (t_i_3d_context *)context;
	proj_mat = get_projection_matrix(i_context->dd_context, proj_type);
	i = 0;
	while (i < model.quad_count)
	{
		if (is_visible(model.quads[i], proj_type, new_vect_3d(0, 0, 0)) == true)
			put_2d_quad(i_context->dd_context, project_3d_quad(i_context,
					model.quads[i], proj_mat));
		i++;
	}
}

static void	put_3d_object(void *object, void *scene)
{
	t_i_3d_scene	*i_scene;
	t_i_3d_object	*obj;
	t_uint32		i;

	i_scene = (t_i_3d_scene *)scene;
	obj = (t_i_3d_object *)object;
	i = 0;
	while (i < obj->mesh.quad_count)
	{
		if (is_visible(obj->mesh.quads[i], i_scene->proj_type,
				new_vect_3d(0, 0, 0)) == true)
			put_2d_quad(i_scene->context->dd_context, project_3d_quad(
					i_scene->context, obj->mesh.quads[i], i_scene->proj_mat));
		i++;
	}
}

void	render_3d_scene(t_3d_scene *scene)
{
	t_i_3d_scene	*i_scene;

	if (scene == NULL)
		return ;
	i_scene = (t_i_3d_scene *)scene;
	lstiter_data(i_scene->object_list, &put_3d_object, i_scene);
}

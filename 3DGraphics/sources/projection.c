/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 18:27:32 by tchoquet          #+#    #+#             */
/*   Updated: 2023/06/30 16:30:28 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DDD_Graphics_internal.h"

static t_3d_quad	to_ddd(t_2d_quad dd_quad);

t_2d_point	project_3d_point(t_i_3d_context *context, t_3d_point point,
				t_mat4x4 proj_mat)
{
	t_vect_3d	proj_pos;

	proj_pos = vect_x_mat(point.pos, proj_mat);
	proj_pos = vector_div(proj_pos, proj_pos.w);
	proj_pos.x += 1.0f;
	proj_pos.y += -1.0f;
	proj_pos.x *= 0.5f * (float)get_2d_context_width(context->dd_context);
	proj_pos.y *= -0.5f * (float)get_2d_context_height(context->dd_context);
	return ((t_2d_point){
		.x = proj_pos.x,
		.y = proj_pos.y,
		.color = point.color});
}

t_2d_quad	project_3d_quad(t_i_3d_context *context, t_3d_quad quad,
				t_mat4x4 proj_mat)
{
	return ((t_2d_quad){
		.p[0] = project_3d_point(context, quad.p[0], proj_mat),
		.p[1] = project_3d_point(context, quad.p[1], proj_mat),
		.p[2] = project_3d_point(context, quad.p[2], proj_mat),
		.p[3] = project_3d_point(context, quad.p[3], proj_mat)}
	);
}

t_3d_model	project_3d_model(t_i_3d_context *context, t_3d_model model,
				t_projection proj_type, t_vect_3d view_point)
{
	t_mat4x4	proj_mat;
	t_3d_model	p_model;
	t_uint32	i;

	proj_mat = get_projection_matrix(context->dd_context, proj_type);
	p_model.quads = malloc(sizeof(t_3d_quad) * model.quad_count);
	if (p_model.quads == NULL)
		return ((t_3d_model){.quads = NULL, .quad_count = 0});
	i = 0;
	p_model.quad_count = 0;
	while (i < model.quad_count)
	{	
		if (is_visible(model.quads[i], proj_type, view_point) == true)
		{
			p_model.quads[i] = to_ddd(project_3d_quad(context,
						model.quads[i], proj_mat));
			p_model.quad_count++;
		}
		i++;
	}
	return (p_model);
}

static t_3d_quad	to_ddd(t_2d_quad dd_quad)
{
	return (
		(t_3d_quad){
		.p[0] = (t_3d_point){
		.pos = new_vect_3d(dd_quad.p[0].x, dd_quad.p[0].y, 0),
		.color = dd_quad.p[0].color},
			.p[1] = (t_3d_point){
				.pos = new_vect_3d(dd_quad.p[1].x, dd_quad.p[1].y, 0),
				.color = dd_quad.p[1].color},
			.p[2] = (t_3d_point){
				.pos = new_vect_3d(dd_quad.p[2].x, dd_quad.p[2].y, 0),
				.color = dd_quad.p[2].color},
			.p[3] = (t_3d_point){
				.pos = new_vect_3d(dd_quad.p[3].x, dd_quad.p[3].y, 0),
				.color = dd_quad.p[3].color},
		}
	);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 13:01:24 by tchoquet          #+#    #+#             */
/*   Updated: 2023/06/30 16:28:52 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DDD_Graphics_internal.h"

void	*map_quads(t_3d_quad *array, size_t len, size_t ret_el_size,
			void *(*func)(t_3d_quad *))
{
	void		*output;
	t_uint32	i;
	void		*fun_res;

	output = malloc(ret_el_size * len);
	if (output == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		fun_res = func(array + i);
		ft_memcpy(output + (i * ret_el_size), fun_res, ret_el_size);
		i++;
	}
	return (output);
}

t_bool	is_visible(t_3d_quad quad, t_projection proj_type, t_vect_3d view_point)
{
	t_vect_3d	normal;

	if (proj_type != perspective)
		return (true);
	normal = cross_product(quad.p[0].pos, quad.p[1].pos, quad.p[2].pos);
	normal = vector_normalise(normal);
	if (vector_dot_product(normal,
			vector_sub(quad.p[0].pos, view_point)) > 0.0f)
		return (false);
	return (true);
}

void	refresh_mesh(t_i_3d_object *object)
{
	t_uint32	t;
	t_uint32	p;

	t = 0;
	while (t < object->source_model.quad_count)
	{	
		object->mesh.quads[t] = object->source_model.quads[t];
		p = 0;
		while (p < 4)
		{
			object->mesh.quads[t].p[p].pos = vect_x_mat(object->mesh.quads[t]
					.p[p].pos, rotation_matrix(object->rotation));
			object->mesh.quads[t].p[p].pos = vect_x_mat(object->mesh.quads[t]
					.p[p].pos, scale_matrix(object->scale));
			object->mesh.quads[t].p[p].pos = vect_x_mat(object->mesh.quads[t]
					.p[p].pos, translate_matrix(object->position));
			p++;
		}
		t++;
	}
}

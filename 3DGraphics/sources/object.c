/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 19:02:08 by tchoquet          #+#    #+#             */
/*   Updated: 2023/06/30 17:29:03 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DDD_Graphics_internal.h"

t_3d_object	*create_3d_object(t_3d_model model)
{
	t_i_3d_object	*new_object;
	t_uint32		i;

	center_3d_model(&model);
	new_object = ft_calloc(1, sizeof(t_i_3d_object));
	if (new_object == NULL)
		return (NULL);
	*new_object = (t_i_3d_object){.source_model.quad_count = model.quad_count,
		.mesh.quad_count = model.quad_count, .scale = new_vect_3d(1, 1, 1)};
	new_object->source_model.quads = malloc(sizeof(t_3d_quad)
			* model.quad_count);
	new_object->mesh.quads = malloc(sizeof(t_3d_quad)
			* model.quad_count);
	if (new_object->source_model.quads == NULL
		|| new_object->mesh.quads == NULL)
		return (del_3d_object((t_3d_object *)new_object));
	i = -1;
	while (++i < model.quad_count)
	{
		new_object->source_model.quads[i] = model.quads[i];
		new_object->mesh.quads[i] = model.quads[i];
	}
	return ((t_3d_object *)new_object);
}

t_3d_object	*del_3d_object(t_3d_object *object)
{
	t_i_3d_object	*obj;

	if (object == NULL)
		return (NULL);
	obj = (t_i_3d_object *)object;
	free(obj->source_model.quads);
	free(obj->mesh.quads);
	free(object);
	return (NULL);
}

void	add_3d_object_to_scene(t_3d_object *obj, t_3d_scene *scene)
{
	t_i_3d_scene	*i_scene;

	if (scene == NULL || obj == NULL)
		return ;
	i_scene = (t_i_3d_scene *)scene;
	ft_lstadd_front(&i_scene->object_list, ft_lstnew(obj));
}

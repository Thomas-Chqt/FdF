/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DDD_Graphics.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:37:21 by tchoquet          #+#    #+#             */
/*   Updated: 2023/06/30 17:26:44 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DDD_Graphics_internal.h"

t_3d_context	*create_3d_context(void *pixels_buffer, t_uint32 width,
					t_uint32 height)
{
	t_2d_context	*dd_context;
	t_i_3d_context	*new_context;

	dd_context = create_2d_context(pixels_buffer, width, height);
	if (dd_context == NULL)
		return (NULL);
	new_context = malloc(sizeof(t_i_3d_context));
	if (new_context == NULL)
		return (NULL);
	new_context->dd_context = dd_context;
	new_context->ddd_scene = NULL;
	return ((t_3d_context *)new_context);
}

t_3d_scene	*get_3d_scene(t_3d_context *context, t_projection proj_type)
{
	t_i_3d_scene	*new_scene;
	t_i_3d_context	*i_context;

	if (context == NULL)
		return (NULL);
	i_context = (t_i_3d_context *)context;
	if (i_context->ddd_scene != NULL)
		return ((t_3d_scene *)i_context->ddd_scene);
	new_scene = malloc(sizeof(t_i_3d_scene));
	if (new_scene == NULL)
		return (NULL);
	new_scene->object_list = NULL;
	new_scene->camera = new_vect_3d(0, 0, 0);
	new_scene->proj_mat = get_projection_matrix(i_context->dd_context,
			proj_type);
	new_scene->context = i_context;
	new_scene->proj_type = proj_type;
	i_context->ddd_scene = new_scene;
	return ((t_3d_scene *)new_scene);
}

void	delete_3d_context(t_3d_context *context)
{
	t_i_3d_context	*i_context;

	if (context == NULL)
		return ;
	i_context = (t_i_3d_context *)context;
	clear_3d_scene((t_3d_scene *)i_context->ddd_scene);
	free(i_context->ddd_scene);
	delete_2d_context(i_context->dd_context);
	free(i_context);
	return ;
}

void	change_projection(t_3d_scene *scene, t_projection new_proj)
{
	t_i_3d_scene	*i_scene;

	if (scene == NULL)
		return ;
	i_scene = (t_i_3d_scene *)scene;
	i_scene->proj_mat
		= get_projection_matrix(i_scene->context->dd_context, new_proj);
	i_scene->proj_type = new_proj;
}

void	clear_3d_scene(t_3d_scene *scene)
{
	t_i_3d_scene	*i_scene;

	i_scene = (t_i_3d_scene *)scene;
	if (i_scene != NULL)
		ft_lstclear(&i_scene->object_list, &del_obj_wrapper);
}

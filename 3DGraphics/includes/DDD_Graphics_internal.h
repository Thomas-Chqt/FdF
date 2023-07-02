/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DDD_Graphics_internal.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:39:07 by tchoquet          #+#    #+#             */
/*   Updated: 2023/06/30 17:16:33 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DDD_GRAPHICS_INTERNAL_H
# define DDD_GRAPHICS_INTERNAL_H

# ifdef MEMCHEK
#  include <memory_leak_detector.h>
# endif // MEMCHEK

# include <DD_Graphics.h>

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>

# include "DDD_Graphics.h"

typedef struct s_i_3d_object	t_i_3d_object;
typedef struct s_i_3d_scene		t_i_3d_scene;
typedef struct s_i_3d_context	t_i_3d_context;

typedef struct s_i_3d_object
{
	t_3d_model	source_model;
	t_vect_3d	rotation;
	t_vect_3d	position;
	t_vect_3d	scale;
	t_3d_model	mesh;

}	t_i_3d_object;

typedef struct s_i_3d_scene
{
	t_list			*object_list;
	t_vect_3d		camera;
	t_mat4x4		proj_mat;
	t_i_3d_context	*context;
	t_projection	proj_type;

}	t_i_3d_scene;

typedef struct s_i_3d_context
{
	t_2d_context	*dd_context;
	t_i_3d_scene	*ddd_scene;

}	t_i_3d_context;

t_3d_model	load_fdf_file(char const *file_path);

t_2d_point	project_3d_point(t_i_3d_context *context, t_3d_point point,
				t_mat4x4 proj_mat);
t_2d_quad	project_3d_quad(t_i_3d_context *context, t_3d_quad quad,
				t_mat4x4 proj_mat);
t_3d_model	project_3d_model(t_i_3d_context *context, t_3d_model model,
				t_projection proj_type, t_vect_3d view_point);

t_3d_object	*del_3d_object(t_3d_object *object);

t_mat4x4	get_projection_matrix(t_2d_context *dd_context,
				t_projection proj_type);

void		*map_quads(t_3d_quad *array, size_t len, size_t ret_el_size,
				void *(*func)(t_3d_quad *));
t_bool		is_visible(t_3d_quad quad, t_projection proj_type,
				t_vect_3d view_point);
void		refresh_mesh(t_i_3d_object *object);

void		*to_x_map(t_3d_quad *quad);
void		*to_y_map(t_3d_quad *quad);
void		*to_z_map(t_3d_quad *quad);
void		del_obj_wrapper(void *object);
void		free_wrapper(void *ptr);

#endif // DDD_GRAPHICS_INTERNAL_H
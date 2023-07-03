/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DDD_Graphics.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:36:48 by tchoquet          #+#    #+#             */
/*   Updated: 2023/06/30 17:16:19 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DDD_GRAPHICS_H
# define DDD_GRAPHICS_H

# define FOV 90.0f
# define F_FAR 0.1f
# define F_NEAR 1000.0f

# include <libft.h>

typedef struct s_3d_context		t_3d_context;
typedef struct s_3d_scene		t_3d_scene;
typedef struct s_3d_object		t_3d_object;

typedef struct s_3d_point		t_3d_point;
typedef struct s_3d_quad		t_3d_quad;
typedef struct s_3d_model		t_3d_model;

typedef enum e_projection		t_projection;

struct s_3d_point
{
	t_vect_3d	pos;
	t_color		color;
};

struct s_3d_quad
{
	t_3d_point	p[4];
};

struct s_3d_model
{	
	t_3d_quad	*quads;
	t_uint32	quad_count;
};

enum e_projection
{
	isometric,
	orthographic,
	perspective
};

t_3d_context	*create_3d_context(void *pixels_buffer, t_uint32 width,
					t_uint32 height);
t_3d_scene		*get_3d_scene(t_3d_context *context, t_projection proj_type);
void			change_projection(t_3d_scene *scene, t_projection new_proj);
void			delete_3d_context(t_3d_context *context);
void			clear_3d_scene(t_3d_scene *scene);

t_3d_model		load_file(char const *file_path);
void			center_3d_model(t_3d_model *model);
t_vect_3d		get_3d_model_size(t_3d_model model);
t_vect_3d		get_projected_size(t_3d_context *context, t_3d_model model,
					t_projection proj_type);

t_3d_object		*create_3d_object(t_3d_model model);
void			add_3d_object_to_scene(t_3d_object *obj, t_3d_scene *scene);

void			rotate_3d_model(t_3d_model *model, t_vect_3d angles);
t_vect_3d		get_3d_object_rotation(t_3d_object *object);
void			set_3d_object_rotation(t_3d_object *object, t_vect_3d rotation);

void			scale_3d_model(t_3d_model *model, t_vect_3d scales);
t_vect_3d		get_3d_object_scale(t_3d_object *object);
void			set_3d_object_scale(t_3d_object *object, t_vect_3d scale);

t_vect_3d		get_3d_object_position(t_3d_object *object);
void			set_3d_object_position(t_3d_object *object, t_vect_3d position);

void			put_3d_model(t_3d_context *context, t_3d_model model,
					t_projection proj_type);
void			render_3d_scene(t_3d_scene *scene);

#endif // DDD_GRAPHICS_H
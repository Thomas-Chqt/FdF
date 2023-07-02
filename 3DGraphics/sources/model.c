/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 19:44:18 by tchoquet          #+#    #+#             */
/*   Updated: 2023/07/02 18:24:28 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DDD_Graphics_internal.h"

static void		flip_z(t_3d_model *model);

t_3d_model	load_file(char const *file_path)
{
	t_3d_model	loaded_model;

	if (ft_strrchr(file_path, '.') != NULL
		&& ft_strncmp(ft_strrchr(file_path, '.'), ".fdf", 4) == 0)
	{
		loaded_model = load_fdf_file(file_path);
		if (loaded_model.quads != NULL)
			flip_z(&loaded_model);
		return (loaded_model);
	}
	else
	{
		return ((t_3d_model){0});
	}
}

void	center_3d_model(t_3d_model *model)
{
	t_vect_3d	av;
	t_uint32	f;
	t_uint32	v;

	av = new_vect_3d(0, 0, 0);
	f = -1;
	while (++f < model->quad_count)
	{
		v = -1;
		while (++v < 4)
			av = vector_add(av, model->quads[f].p[v].pos);
	}
	av = vector_div(av, model->quad_count * 4);
	f = -1;
	while (++f < model->quad_count)
	{
		v = -1;
		while (++v < 4)
			model->quads[f].p[v].pos
				= vector_sub(model->quads[f].p[v].pos, av);
	}
}

t_vect_3d	get_3d_model_size(t_3d_model model)
{
	t_vect_3d	size;
	float		*farray;
	t_uint32	qc;

	qc = model.quad_count;
	farray = map_quads(model.quads, qc, sizeof(float) * 4, &to_x_map);
	if (farray == NULL)
		return ((t_vect_3d){0, 0, 0, 0});
	size.x = *((float *)find_best(farray, qc * 4, sizeof(float), &fbigest))
		- *((float *)find_best(farray, qc * 4, sizeof(float), &fsmallest));
	free(farray);
	farray = map_quads(model.quads, qc, sizeof(float) * 4, &to_y_map);
	if (farray == NULL)
		return ((t_vect_3d){0, 0, 0, 0});
	size.y = *((float *)find_best(farray, qc * 4, sizeof(float), &fbigest))
		- *((float *)find_best(farray, qc * 4, sizeof(float), &fsmallest));
	free(farray);
	farray = map_quads(model.quads, qc, sizeof(float) * 4, &to_x_map);
	if (farray == NULL)
		return ((t_vect_3d){0, 0, 0, 0});
	size.z = *((float *)find_best(farray, qc * 4, sizeof(float), &fbigest))
		- *((float *)find_best(farray, qc * 4, sizeof(float), &fsmallest));
	free(farray);
	return (size);
}

t_vect_3d	get_projected_size(t_3d_context *context, t_3d_model model,
				t_projection proj_type)
{
	t_i_3d_context	*i_context;
	t_3d_model		p_model;
	t_vect_3d		size;

	if (context == NULL)
		return ((t_vect_3d){0, 0, 0, 0});
	i_context = (t_i_3d_context *)context;
	p_model = project_3d_model(i_context, model, proj_type,
			new_vect_3d(0, 0, 0));
	if (p_model.quads == NULL)
		return ((t_vect_3d){0, 0, 0, 0});
	size = get_3d_model_size(p_model);
	free(p_model.quads);
	return (size);
}

static void	flip_z(t_3d_model *model)
{
	float		*all_z;
	float		bigest_z;
	t_uint32	i;

	all_z = (float *)map_quads(model->quads, model->quad_count,
			sizeof(float) * 4, &to_z_map);
	bigest_z = *((float *)find_best(all_z, model->quad_count * 4,
				sizeof(float), &fbigest));
	free(all_z);
	i = 0;
	while (i < model->quad_count)
	{
		model->quads[i].p[0].pos.z = bigest_z - model->quads[i].p[0].pos.z;
		model->quads[i].p[1].pos.z = bigest_z - model->quads[i].p[1].pos.z;
		model->quads[i].p[2].pos.z = bigest_z - model->quads[i].p[2].pos.z;
		model->quads[i].p[3].pos.z = bigest_z - model->quads[i].p[3].pos.z;
		i++;
	}
}

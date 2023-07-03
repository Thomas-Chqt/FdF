/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 13:11:14 by tchoquet          #+#    #+#             */
/*   Updated: 2023/06/30 16:41:54 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DDD_Graphics_internal.h"

void	*to_x_map(t_3d_quad *quad)
{
	static float	x[4];

	x[0] = quad->p[0].pos.x;
	x[1] = quad->p[1].pos.x;
	x[2] = quad->p[2].pos.x;
	x[3] = quad->p[3].pos.x;
	return ((void *)x);
}

void	*to_y_map(t_3d_quad *quad)
{
	static float	y[4];

	y[0] = quad->p[0].pos.y;
	y[1] = quad->p[1].pos.y;
	y[2] = quad->p[2].pos.y;
	y[3] = quad->p[3].pos.y;
	return ((void *)y);
}

void	*to_z_map(t_3d_quad *quad)
{
	static float	z[4];

	z[0] = quad->p[0].pos.z;
	z[1] = quad->p[1].pos.z;
	z[2] = quad->p[2].pos.z;
	z[3] = quad->p[3].pos.z;
	return ((void *)z);
}

void	del_obj_wrapper(void *object)
{
	(void)del_3d_object((t_3d_object *)object);
}

void	free_wrapper(void *ptr)
{
	free(ptr);
}

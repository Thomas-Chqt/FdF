/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 16:10:56 by tchoquet          #+#    #+#             */
/*   Updated: 2023/06/30 16:27:52 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DDD_Graphics_internal.h"

t_vect_3d	get_3d_object_position(t_3d_object *object)
{
	if (object == NULL)
		return (new_vect_3d(-1, -1, -1));
	return (((t_i_3d_object *)object)->position);
}

void	set_3d_object_position(t_3d_object *object, t_vect_3d position)
{
	if (object == NULL)
		return ;
	((t_i_3d_object *)object)->position = position;
	refresh_mesh((t_i_3d_object *)object);
}

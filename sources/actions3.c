/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 18:36:14 by tchoquet          #+#    #+#             */
/*   Updated: 2023/06/30 19:06:26 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	click(int x, int y, void *data)
{
	t_setup_data	*setup_data;

	setup_data = (t_setup_data *)data;
	if (setup_data->rotation == true)
		return ;
	if (setup_data->clicked == true)
		setup_data->clicked = false;
	else
	{
		setup_data->clicked = true;
		setup_data->src_x = x;
		setup_data->src_y = y;
		setup_data->src_rot = get_3d_object_rotation(setup_data->map);
	}
}

void	move(int x, int y, void *data)
{
	t_setup_data	*setup_data;
	int				dist_x;
	int				dist_y;

	setup_data = (t_setup_data *)data;
	if (setup_data->rotation == true)
		return ;
	if (setup_data->clicked == true)
	{
		dist_x = x - setup_data->src_x;
		dist_y = y - setup_data->src_y;
		setup_data->new_rot = setup_data->src_rot;
		setup_data->new_rot.y -= (dist_x / 10);
		setup_data->new_rot.x -= (dist_y / 10);
		set_3d_object_rotation(setup_data->map, setup_data->new_rot);
	}
}

void	toggle_rot(void *data)
{
	t_setup_data	*setup_data;

	setup_data = (t_setup_data *)data;
	if (setup_data->clicked == true)
		return ;
	if (setup_data->rotation == true)
		setup_data->rotation = false;
	else
		setup_data->rotation = true;
}

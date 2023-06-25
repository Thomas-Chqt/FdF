/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 01:59:33 by tchoquet          #+#    #+#             */
/*   Updated: 2023/06/25 19:14:48 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_setup_data	*return_error(t_setup_data *setup_data, t_uint32 code);

t_setup_data	*init_setup_data(t_window *window, int argc, char const *argv[])
{
	static t_setup_data	setup_data;

	if (window == NULL)
		return(return_error(&setup_data, UNKNOWN_ERROR));
	setup_data.arguments = parse_arguments(argc, argv);
	if (setup_data.arguments == NULL)
		return(return_error(&setup_data, errno));
	setup_data.ddd_context = create_3d_context(get_pixel_buffer(window), WIDTH, HEIGHT, false);
	if (setup_data.ddd_context == NULL)
		return(return_error(&setup_data, UNKNOWN_ERROR));
	setup_data.scene = get_3d_scene(setup_data.ddd_context, isometric);
	if (setup_data.scene == NULL)
		return(return_error(&setup_data, UNKNOWN_ERROR));
	setup_data.original_model = load_file(setup_data.arguments->map_file);
	if (setup_data.original_model.poly_count == 0)
		return(return_error(&setup_data, UNKNOWN_ERROR));
	return (&setup_data);
}

static t_setup_data	*return_error(t_setup_data *setup_data, t_uint32 code)
{	
	free_setup_data(setup_data);
	errno = code;
	return (NULL);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 02:01:01 by tchoquet          #+#    #+#             */
/*   Updated: 2023/06/24 19:49:21 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#ifdef MEMCHEK

__attribute__((destructor))
static void	destructor(void)
{
	print_report();
}

#endif // MEMCHEK

int	main(int argc, char const *argv[])
{
	t_setup_data	*setup_data;

	setup_data = init_setup_data(argc, argv);
	swich_to_iso(NULL, setup_data);
	start_main_loop(setup_data->window, &main_loop,
		setup_data, &free_setup_data);
	return (0);
}

void	main_loop(t_window *window, void *data)
{
	t_setup_data	*setup_data;

	window = NULL;
	setup_data = (t_setup_data *)data;
	render_3d_scene(setup_data->scene);
}

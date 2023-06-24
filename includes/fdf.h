/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 01:59:21 by tchoquet          #+#    #+#             */
/*   Updated: 2023/06/24 20:03:44 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define USE_QUADRILATERAL

# ifdef MEMCHEK
#  include <memory_leak_detector.h>
# endif // MEMCHEK

# include <stdlib.h>
# include <sys/errno.h>

# include <ft_printf.h>
# include <wrapped_mlx.h>
# include <libft.h>
# include <DDD_Graphics.h>
# include <math.h>

# define WIDTH 1280
# define HEIGHT 720

# define NO_ARGS -1111
# define ERROR_PARSING_ARGS -2222
# define UNKNOWN_ERROR -3333
# define NO_MAP -4444
# define MAP_READ_ERROR -5555

typedef struct s_setup_data	t_setup_data;
typedef struct s_arguments	t_arguments;
typedef struct s_option		t_option;

struct s_setup_data
{
	t_arguments		*arguments;
	t_window		*window;
	t_3d_context	*ddd_context;
	t_3d_scene		*scene;
	t_3d_model		original_model;
	t_3d_object		*map;
};

struct s_arguments
{
	t_bool		help;
	t_color		colors1;
	t_color		colors2;
	t_color		colors3;
	char		*map_file;
};

void			main_loop(t_window *window, void *data);

void			swich_to_iso(t_window *window, void *data);

t_arguments		*parse_arguments(int argc, char const *argv[]);
void			free_arguments(t_arguments	*args);

t_setup_data	*init_setup_data(int argc, char const *argv[]);
void			free_setup_data(void *data);
float			get_height_iso(t_3d_model model);

void			exit_error(int new_errno, void (free_func)(void *), void *data);
void			print_help(void);

#endif // FDF_H
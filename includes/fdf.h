/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 01:59:21 by tchoquet          #+#    #+#             */
/*   Updated: 2023/06/23 14:28:54 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <sys/errno.h>

# include <ft_printf.h>
# include <wrapped_mlx.h>
# include <libft.h>

# define NO_ARGS 1111

typedef struct s_setup_data	t_setup_data;
typedef	struct s_arguments	t_arguments;
typedef struct s_option		t_option;

struct s_setup_data
{
	t_arguments	*arguments;
};

struct s_arguments
{
	t_option	*options;
	t_uint32	option_count;
	char		*map_file;
};

struct s_option
{
	char	*name;
	void	*data;
};

t_arguments	*parse_arguments(int argc, char const *argv[]);
void		free_arguments(t_arguments	*args);

#endif // FDF_H
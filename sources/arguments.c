/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 14:14:02 by tchoquet          #+#    #+#             */
/*   Updated: 2023/06/24 16:44:13 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_arguments	*return_error(t_arguments *args, t_uint32 code);
static int			parse_option(t_arguments *args, int *i, int argc,
						char const *argv[]);
static int			parse_color(t_color *color, char const *str);

t_arguments	*parse_arguments(int argc, char const *argv[])
{
	t_arguments	*args;
	int			i;

	args = ft_calloc(1, sizeof(t_arguments));
	if (args == NULL)
		return (return_error(args, UNKNOWN_ERROR));
	if (argc < 2)
		return (return_error(args, NO_ARGS));
	args->colors1 = (t_color)WHITE;
	args->colors2 = (t_color)WHITE;
	args->colors3 = (t_color)WHITE;
	i = 0;
	while (++i < argc)
	{
		if (argv[i][0] != '-' && args->map_file == NULL)
			args->map_file = ft_strdup(argv[i]);
		else if (parse_option(args, &i, argc, argv) != 0)
			return (return_error(args, ERROR_PARSING_ARGS));
	}
	if (args->map_file == NULL && args->help == false)
		return (return_error(args, NO_MAP));
	return (args);
}

void	free_arguments(t_arguments	*args)
{
	if (args == NULL)
		return ;
	free(args->map_file);
}

static t_arguments	*return_error(t_arguments *args, t_uint32 code)
{	
	free_arguments(args);
	errno = code;
	return (NULL);
}

static int	parse_option(t_arguments *args, int *i, int argc,
				char const *argv[])
{
	if (ft_strncmp(argv[*i] + 1, "h", 1) == 0)
	{
		args->help = true;
		return (0);
	}
	if ((ft_strncmp(argv[*i] + 1, "c1", 2) == 0) && ((*i) + 1 < argc))
		return (parse_color(&args->colors1, argv[++(*i)]));
	if ((ft_strncmp(argv[*i] + 1, "c2", 2) == 0) && ((*i) + 1 < argc))
		return (parse_color(&args->colors2, argv[++(*i)]));
	if ((ft_strncmp(argv[*i] + 1, "c3", 2) == 0) && ((*i) + 1 < argc))
		return (parse_color(&args->colors3, argv[++(*i)]));
	return (-1);
}

static int	parse_color(t_color *color, char const *str)
{
	if (ft_strncmp(str, "RED", 3) == 0)
	{
		*color = (t_color)RED;
		return (0);
	}
	if (ft_strncmp(str, "GREEN", 5) == 0)
	{
		*color = (t_color)GREEN;
		return (0);
	}
	if (ft_strncmp(str, "BLUE", 4) == 0)
	{
		*color = (t_color)BLUE;
		return (0);
	}
	return (-1);
}

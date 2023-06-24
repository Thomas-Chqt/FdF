/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 14:14:02 by tchoquet          #+#    #+#             */
/*   Updated: 2023/06/24 11:36:51 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define NBR_OPTION 4

static t_arguments	*return_error(t_arguments *args, t_uint32 code);

t_arguments	*parse_arguments(int argc, char const *argv[])
{
	t_arguments	*args;
	t_uint32	i;
	static char	*options[] = {"h", "c1", "c2", "c3"};

	args = ft_calloc(1, sizeof(t_arguments));
	if (argc < 2)
		return (return_error(args, NO_ARGS));
	i = 1;
	while (i < argc)
	{
		if (argv[i][0] != '-')
			args->map_file = ft_strdup(argv[i]);
	}
}

static t_arguments	*return_error(t_arguments *args, t_uint32 code)
{	
	free_arguments(args);
	errno = code;
	return (NULL);
}

void	free_arguments(t_arguments	*args)
{
	t_uint32	i;

	i = 0;
	while (args != NULL && i < args->option_count)
	{
		free(args->options[i].name);
		free(args->options[i].data);
	}
	free(args->map_file);
}
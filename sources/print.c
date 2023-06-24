/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 17:43:28 by tchoquet          #+#    #+#             */
/*   Updated: 2023/06/24 19:17:03 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	exit_error(int new_errno, void (free_func)(void *), void *data)
{
	if (new_errno != 0)
		errno = new_errno;
	if (errno == NO_ARGS || errno == NO_MAP)
	{
		ft_printf("No map provided, please run fdf like this :\n");
		print_help();
	}
	else if (errno == ERROR_PARSING_ARGS)
	{
		ft_printf("Please run fdf like this :\n");
		print_help();
	}
	else
	{
		ft_printf("Unknown error.\n");
	}
	free_func(data);
	exit(errno);
}

void	print_help(void)
{
	ft_printf("./fdf [-h] [-c1] [-c2] [-c3] file\n");
}

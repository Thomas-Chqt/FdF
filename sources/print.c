/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 17:43:28 by tchoquet          #+#    #+#             */
/*   Updated: 2023/06/25 18:52:07 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_error(int error_code)
{
	if (error_code == NO_ARGS || error_code == NO_MAP)
	{
		ft_printf("No map provided, please run fdf like this :\n");
		print_help();
	}
	else if (error_code == ERROR_PARSING_ARGS)
	{
		ft_printf("Please run fdf like this :\n");
		print_help();
	}
	else
	{
		ft_printf("Unknown error.\n");
	}
}

void	print_help(void)
{
	ft_printf("./fdf [-h] [-c1] [-c2] [-c3] file\n");
}

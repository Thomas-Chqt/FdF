/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 16:53:34 by tchoquet          #+#    #+#             */
/*   Updated: 2023/06/30 17:15:27 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	print_error(int error_code)
{
	if (error_code == NO_MAP)
		ft_printf("No map provided.\n");
	else if (error_code == READ_ERROR)
		ft_printf("Error while reading map file.\n");
	else
		ft_printf("Unknown error.\n");
	return (error_code);
}

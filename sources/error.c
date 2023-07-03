/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 16:53:34 by tchoquet          #+#    #+#             */
/*   Updated: 2023/07/02 18:34:47 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	print_error(int error_code)
{
	if (error_code == NO_MAP)
		write(1, "No map provided.\n", 17);
	else if (error_code == READ_ERROR)
		write(1, "Error while reading map file.\n", 30);
	else
		write(1, "Unknown error.\n", 15);
	return (error_code);
}

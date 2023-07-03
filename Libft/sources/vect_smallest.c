/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_smallest.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 16:29:29 by tchoquet          #+#    #+#             */
/*   Updated: 2023/06/29 16:50:06 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_internal.h"

t_bool	vect_smallest(void *a, void *b)
{
	return ((((t_vect_3d *)b)->x <= ((t_vect_3d *)a)->x)
		&& (((t_vect_3d *)b)->y <= ((t_vect_3d *)a)->y)
		&& (((t_vect_3d *)b)->z <= ((t_vect_3d *)a)->z));
}

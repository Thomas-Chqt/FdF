/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foreach.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 16:13:12 by tchoquet          #+#    #+#             */
/*   Updated: 2023/06/29 16:16:02 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_internal.h"

void	foreach(void *array, size_t len, size_t el_size, void (*func)(void *))
{
	size_t	i;

	if (array == NULL || func == NULL)
		return ;
	i = 0;
	while (i < len)
	{
		func((void *)(((t_uint8 *)array) + (i * el_size)));
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_index.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 12:10:59 by tchoquet          #+#    #+#             */
/*   Updated: 2023/06/25 15:56:51 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_internal.h"

size_t	first_index(unsigned char value, void *buffer, size_t buffer_len)
{
	size_t	i;

	i = 0;
	while (i < buffer_len)
	{
		if (((unsigned char *)buffer)[i] == value)
			return (i);
		i++;
	}
	return (i - 1);
}

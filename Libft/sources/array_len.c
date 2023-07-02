/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_len.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 15:29:35 by tchoquet          #+#    #+#             */
/*   Updated: 2023/06/25 15:56:02 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_internal.h"

size_t	array_len(void *array, size_t element_size)
{
	size_t	len;
	t_uint8	*readable_array;
	t_uint8	*end_bytes;

	if (array == NULL)
		return (0);
	readable_array = (t_uint8 *)array;
	end_bytes = ft_calloc(1, element_size);
	len = 0;
	while (ft_memcmp(readable_array + (len * element_size),
			end_bytes, element_size) != 0)
		len ++;
	free(end_bytes);
	return (len);
}

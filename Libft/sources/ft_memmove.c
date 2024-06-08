/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 14:01:07 by tchoquet          #+#    #+#             */
/*   Updated: 2024/06/08 19:18:40 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_internal.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	long long	i;

	if (dst == NULL || src == NULL)
		return (NULL);
	if ((((char*)src + len) > (char*)dst) && (((char*)dst + len) >
        ((char*)src + len)))
	{
		i = len - 1;
		while (i >= 0)
		{
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
			i--;
		}
	}
	else
	{
		ft_memcpy(dst, src, len);
	}
	return (dst);
}

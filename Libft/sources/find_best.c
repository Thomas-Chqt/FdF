/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_best.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 12:26:25 by tchoquet          #+#    #+#             */
/*   Updated: 2023/06/29 12:43:12 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_internal.h"

void	*find_best(void *array, size_t array_len, size_t el_size,
			t_bool (*diff)(void *, void *))
{
	size_t	i;
	void	*best;

	if (array == NULL || diff == NULL)
		return (NULL);
	best = array;
	i = 1;
	while (i < array_len)
	{
		if (diff(best, (void *)(((t_uint8 *)array) + (i * el_size))) == true)
			best = (void *)(((t_uint8 *)array) + (i * el_size));
		i++;
	}
	return (best);
}

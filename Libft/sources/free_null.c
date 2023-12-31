/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_null.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 12:57:11 by tchoquet          #+#    #+#             */
/*   Updated: 2023/06/26 12:57:44 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_internal.h"

void	free_null(void **ptr)
{
	free(*ptr);
	(*ptr) = NULL;
}

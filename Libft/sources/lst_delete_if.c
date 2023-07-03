/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_delete_if.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 13:42:49 by tchoquet          #+#    #+#             */
/*   Updated: 2023/07/03 13:55:54 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_internal.h"

void	lst_delete_if(t_list **head, void (*del)(void *),
			t_bool (*condition)(void *, void *), void *data)
{
	t_list	*current;
	t_list	*temp;

	if (head == NULL || (*head) == NULL || condition == NULL || del == NULL)
		return ;
	if (condition((*head)->data, data) == true)
	{
		temp = *head;
		*head = (*head)->next;
		del(temp->data);
		free(temp);
	}
	current = *head;
	while (current->next != NULL)
	{
		if (condition(current->next->data, data) == true)
		{
			temp = current->next;
			current->next = current->next->next;
			del(temp->data);
			free(temp);
		}
		else
			current = current->next;
	}
}

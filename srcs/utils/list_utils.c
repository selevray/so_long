/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selevray <selevray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 16:07:40 by selevray          #+#    #+#             */
/*   Updated: 2026/02/10 19:17:48 by selevray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	add_bottom(t_list **head, t_list *new)
{
	t_list	*current;

	if (*head == NULL)
	{
		*head = new;
		new->next = NULL;
		return ;
	}
	current = *head;
	while (current->next != NULL)
		current = current->next;
	current->next = new;
}


void free_list(t_list *head)
{
    t_list *temp;
    
    while (head)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}


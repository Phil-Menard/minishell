/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:18:18 by lefoffan          #+#    #+#             */
/*   Updated: 2025/03/06 14:40:43 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!new)
		return ;
	last = ft_lstlast(*lst);
	if (!last)
	{
		*lst = new;
		return ;
	}
	last->next = new;
}

/*-- TEST --*/
/* 
#include <stdio.h>

int	main(void)
{
	t_list	*head;

	head = ft_lstnew(1);
	ft_lstadd_back(&head, ft_lstnew(2));
	printf("%d, %d\n", (int) head->content, (int) head->next->content);
	free(head->next);
	free(head);
	return (0);
} */
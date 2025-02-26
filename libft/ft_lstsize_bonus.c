/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:17:50 by lefoffan          #+#    #+#             */
/*   Updated: 2024/11/15 15:14:46 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	size;

	size = 0;
	while (lst != NULL)
	{
		size += 1;
		lst = lst->next;
	}
	return (size);
}

/* -- TESTS -- */
/* 
#include <stdio.h>

void	ft_print_lst(t_list *list)
{
	while (list != NULL)
	{
		printf("%d ", (int) list->content);
		list = list->next;
	}
}

int	main(void)
{
	t_list	*first;
	t_list	*second;
	t_list	*third;

	first->content = 1;
	first->next = second;

	second->content = 2;
	second->next = third;

	third->content = 3;
	third->next = NULL;

	ft_print_lst(first);
	return (0);
}
 */
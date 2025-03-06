/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 14:44:25 by lefoffan          #+#    #+#             */
/*   Updated: 2025/03/06 14:40:32 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

/* -- TESTS -- */

// #include <stdio.h>

// int	main(void)
// {
// 	t_list	*head;

// 	head = ft_lstnew("Hello world !");
// 	if (head->content)
// 		printf("%s\n", (char *) head->content);
// 	else
// 		printf("Error\n");
//free(head);
// 	return (0);
// }
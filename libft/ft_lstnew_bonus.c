/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 14:44:25 by lefoffan          #+#    #+#             */
/*   Updated: 2025/02/26 12:21:16 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_libft	*ft_lstnew(void *content)
{
	t_libft	*new_node;

	new_node = malloc(sizeof(t_libft));
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
// 	t_libft	*head;

// 	head = ft_lstnew("Hello world !");
// 	if (head->content)
// 		printf("%s\n", (char *) head->content);
// 	else
// 		printf("Error\n");
//free(head);
// 	return (0);
// }
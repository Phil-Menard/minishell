/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 17:54:24 by lefoffan          #+#    #+#             */
/*   Updated: 2025/02/26 12:21:11 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_libft **lst, void (*del)(void*))
{
	t_libft	*tmp;
	t_libft	*cur;

	cur = *lst;
	while (cur)
	{
		tmp = cur->next;
		del(cur->content);
		free(cur);
		cur = tmp;
	}
	*lst = NULL;
}

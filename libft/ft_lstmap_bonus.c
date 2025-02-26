/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 11:34:17 by lefoffan          #+#    #+#             */
/*   Updated: 2025/02/26 12:21:16 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_libft	*ft_lstmap(t_libft *lst, void *(*f)(void *), void (*del)(void *))
{
	t_libft	*res;

	if (!lst)
		return (NULL);
	res = ft_lstnew(f(lst->content));
	lst = lst->next;
	while (lst)
	{
		ft_lstadd_back(&res, ft_lstnew(f(lst->content)));
		if (!res->content)
		{
			ft_lstclear(&res, del);
			return (NULL);
		}
		lst = lst->next;
	}
	return (res);
}

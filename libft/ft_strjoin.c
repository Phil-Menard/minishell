/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 15:09:06 by lefoffan          #+#    #+#             */
/*   Updated: 2024/11/13 12:00:20 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	len;

	len = ft_strlen(s1) + ft_strlen(s2);
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	while (*s1)
	{
		*res = *s1;
		s1++;
		res++;
	}
	while (*s2)
	{
		*res = *s2;
		res++;
		s2++;
	}
	*res = '\0';
	return (res - len);
}

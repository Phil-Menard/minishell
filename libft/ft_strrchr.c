/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmenard <pmenard@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 09:45:43 by lefoffan          #+#    #+#             */
/*   Updated: 2025/02/26 14:40:42 by pmenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	len;

	len = ft_strlen(s);
	s += len;
	while (len >= 0)
	{
		if (*s == (char) c)
			return ((char *)s);
		s--;
		len--;
	}
	return (NULL);
}

//////////////////// TEST
/*
#include <stdio.h>

int	main(void)
{
	char	*res;

	res = ft_strrchr("sal\0ut ca \\0 va\0\0\0\0\0", 0);
	if (*res == '\0')
		printf("\\0 Found !\n");
	else if (res)
		printf("Found !\n%s\n", res);
	else
		printf("Not Found...\n");
	return (0);
}*/

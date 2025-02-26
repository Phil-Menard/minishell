/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 09:45:43 by lefoffan          #+#    #+#             */
/*   Updated: 2024/11/18 17:44:19 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	len;

	len = ft_strlen(s);
	while (s[len] != (char) c)
	{
		if (len < 0)
			return (NULL);
		len--;
	}
	return ((char *) s + len);
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

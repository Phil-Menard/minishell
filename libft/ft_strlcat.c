/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 12:07:18 by lefoffan          #+#    #+#             */
/*   Updated: 2024/11/14 00:55:17 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	slen;
	size_t	dlen;
	size_t	i;

	slen = ft_strlen(src);
	dlen = ft_strlen(dst);
	i = 0;
	if (size <= dlen)
		return (size + slen);
	while (src[i] && i < size - dlen - 1)
	{
		dst[dlen + i] = src[i];
		i++;
	}
	dst[dlen + i] = '\0';
	return (dlen + slen);
}

////// TESTS
/*
int	main(int ac, char **av)
{
	size_t	result;

	if (ac == 4)
	{
		result = ft_strlcat(av[1], av[2], (size_t) ft_atoi(av[3]));
		printf("%zu\n", result);
		printf("%s\n", av[1]);
		return (0);
	}
	printf("Error\n");
	return (1);
}*/

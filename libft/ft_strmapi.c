/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:04:06 by lefoffan          #+#    #+#             */
/*   Updated: 2024/11/13 16:46:40 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*dst;
	size_t	len_s;
	size_t	i;

	len_s = ft_strlen(s);
	dst = malloc(sizeof(char) * (len_s + 1));
	if (!dst)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dst[i] = (*f)(i, s[i]);
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

/////////////////////
/*
#include <stdio.h>

// si c est une lettre en pos pair et min -> maj
static char	ft_up_pair(unsigned int i, char c)
{
	if ((i % 2 == 0) && (c >= 'a' && c <= 'z'))
		return (c - ('a' - 'A'));
	return (c);
}

int	main(void)
{
	char	src[] = "Hello World !";
	char	*dst;

	dst = ft_strmapi(src, &ft_up_pair);
	if (dst)
		printf("%s\n", dst);
	else
		printf("Error\n");
	free(dst);
	return (0);
}*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 09:38:09 by lefoffan          #+#    #+#             */
/*   Updated: 2024/11/18 17:44:56 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s != (char) c)
	{
		if (*s == '\0' && (char) c != '\0')
			return (NULL);
		s++;
	}
	return ((char *) s);
}

//////////////////// TEST
/*
#include <stdio.h>

int	main(int ac, char **av)
{
	char	*res;

	if (ac == 3) // pour le test avec '\0' mettre 2
	{
		res = ft_strchr(av[1], av[2][0]); // pour le test avec '\0' mettre 0
		if (res)
			printf("Found !\n%s\n", res);
		else
			printf("Not Found...\n%s\n", res);
		return (0);
	}
	printf("Error\n");
	return (1);
}*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 09:34:35 by lefoffan          #+#    #+#             */
/*   Updated: 2024/11/12 17:32:01 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}

////////// TEST 
/*
#include <stdio.h>

int	main(int ac, char **av)
{
	if (ac == 2)
	{
		printf("%c\n%c\n", av[1][0], (char) ft_toupper((int) av[1][0]));
		return (0);
	}
	printf("Error\n");
	return (1);
}*/

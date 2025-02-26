/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:52:01 by lefoffan          #+#    #+#             */
/*   Updated: 2024/11/08 11:18:20 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*x;

	x = (unsigned char *) s;
	while (n)
	{
		n--;
		x[n] = 0;
	}
}

/////////////////////
/*
#include <stdio.h>

int	main(void)
{
	int	tab[5];
	int	i;

	i = 0;
	//tab = malloc(sizeof(int) * 5);
	ft_bzero(tab, 5 * sizeof(int));
	while (i < 5)
		printf("%d\n", tab[i++]);
	//free(tab);
	return (0);
}*/

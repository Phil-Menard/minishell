/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:28:27 by lefoffan          #+#    #+#             */
/*   Updated: 2024/11/18 16:18:11 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_int_len(long int n)
{
	size_t	size;

	if (n == 0)
		return (1);
	size = 0;
	if (n < 0)
	{
		size++;
		n *= -1;
	}
	while (n)
	{
		size++;
		n /= 10;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char		*res;
	size_t		len;
	size_t		i;
	long int	nbr;

	i = 0;
	nbr = (long int) n;
	len = ft_int_len(nbr);
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	if (nbr < 0)
	{
		nbr *= -1;
		res[0] = '-';
		i = 1;
	}
	res[len] = '\0';
	while (len > i)
	{
		res[--len] = '0' + (nbr % 10);
		nbr /= 10;
	}
	return (res);
}

/////////////////////////////////////////////////////
/* 
#include <stdio.h>
#include <limits.h>

int	main(void)
{
	char	*res;

	res = ft_itoa(INT_MAX);
	if (res)
		printf("%s\n", res);
	else
		printf("null\n");
	free(res);
	return (0);
}
 */
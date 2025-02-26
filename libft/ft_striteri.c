/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:48:23 by lefoffan          #+#    #+#             */
/*   Updated: 2024/11/13 17:01:03 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		(*f)(i, &s[i]);
		i++;
	}
}

/////////////////////////////
/*
#include <stdio.h>

// si c est une lettre en pos pair et min -> maj
static void	ft_up_pair(unsigned int i, char *c)
{
	if ((i % 2 == 0) && (*c >= 'a' && *c <= 'z'))
		*c = (*c - ('a' - 'A'));
}

int	main(void)
{
	char	str[] = "Hello World !";

	ft_striteri(str, &ft_up_pair);
	printf("%s\n", str);
	return (0);
}*/

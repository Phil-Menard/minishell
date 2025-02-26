/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 10:02:29 by lefoffan          #+#    #+#             */
/*   Updated: 2024/11/18 16:25:38 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*x1;
	unsigned char	*x2;
	size_t			i;

	i = 0;
	x1 = (unsigned char *) s1;
	x2 = (unsigned char *) s2;
	while (n && (x1[i] == x2[i]))
	{
		n--;
		i++;
	}
	if (!n)
		return (0);
	return ((int) x1[i] - (int) x2[i]);
}

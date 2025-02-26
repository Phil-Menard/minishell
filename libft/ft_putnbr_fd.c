/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:06:26 by lefoffan          #+#    #+#             */
/*   Updated: 2024/11/13 17:10:40 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long int	nbr;
	char		res;

	nbr = (long int) n;
	if (nbr < 0)
	{
		write(fd, "-", 1);
		nbr *= -1;
	}
	if (nbr >= 10)
		ft_putnbr_fd(nbr / 10, fd);
	res = (nbr % 10) + '0';
	write(fd, &res, 1);
}

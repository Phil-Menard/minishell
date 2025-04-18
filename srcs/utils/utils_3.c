/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmenard <pmenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:10:11 by lefoffan          #+#    #+#             */
/*   Updated: 2025/04/16 15:29:53 by pmenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_str_isalpha(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}

long int	ft_atol(char *nptr)
{
	long int	res;
	int			sign;

	res = 0;
	sign = 1;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == ' ')
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign *= -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		res = (res * 10) + (*nptr - '0');
		nptr++;
	}
	return (res * sign);
}

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

char	*ft_ltoa(long int n)
{
	char		*res;
	size_t		len;
	size_t		i;
	long int	nbr;

	i = 0;
	nbr = n;
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

char	*parse_exit_arg(char *str)
{
	char	*res;
	int		i;
	int		sign;

	i = 0;
	sign = 0;
	res = NULL;
	if (str[i] == '-')
	{
		res = ft_straddchar(res, str[i]);
		sign++;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] == '0')
		i++;
	res = ft_straddstr(res, str + i);
	free(str);
	return (res);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmenard <pmenard@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:25:33 by lefoffan          #+#    #+#             */
/*   Updated: 2025/02/26 14:40:08 by pmenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countnbstring(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	int		j;
	char	**tab;
	size_t	start;
	size_t	end;

	tab = (char **) malloc ((ft_countnbstring(s, c) + 1) * sizeof(char *));
	if (tab == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		end = i;
		if (end > start)
			tab[j++] = ft_substr(s, start, end - start);
	}
	tab[j] = 0;
	return (tab);
}

///////////////////
/*
#include <stdio.h>

int	main(int ac, char **av)
{
	char	**split;
	size_t	i;

	if (ac == 3)
	{
		split = ft_split(av[1], av[2][0]);
		i = 0;
		while (split[i] != NULL)
		{
			printf("string %zu : %s\n", i, split[i]);
			i++;
		}
		i = 0;
		while (split[i])
			free(split[i++]);
		free(split);
		return (0);
	}
	printf("ERROR\n");
	return (1);
}*/

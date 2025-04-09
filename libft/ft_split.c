/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmenard <pmenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:25:33 by lefoffan          #+#    #+#             */
/*   Updated: 2025/04/09 13:33:27 by pmenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_charset(char c, char *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

static int	ft_countnbstring(char const *s, char *charset)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && is_charset(s[i], charset) == 1)
			i++;
		if (s[i])
			count++;
		while (s[i] && is_charset(s[i], charset) == 0)
			i++;
	}
	return (count);
}

char	**ft_split(char const *s, char *charset)
{
	size_t	i;
	int		j;
	char	**tab;
	size_t	start;
	size_t	end;

	tab = (char **) malloc((ft_countnbstring(s, charset) + 1) * sizeof(char *));
	if (tab == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && is_charset(s[i], charset) == 1)
			i++;
		start = i;
		while (s[i] && is_charset(s[i], charset) == 0)
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

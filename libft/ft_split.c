/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:25:33 by lefoffan          #+#    #+#             */
/*   Updated: 2024/11/18 15:24:31 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_word(const char *s, char c)
{
	size_t	cw;

	cw = 0;
	while (*s)
	{
		if (*s != c)
			cw++;
		while (*s != c && *s && *(s + 1))
			s++;
		s++;
	}
	return (cw);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	size_t	i;
	size_t	j;
	size_t	lenword;

	j = 0;
	split = malloc(sizeof(char *) * (ft_count_word(s, c) + 1));
	if (!split)
		return (NULL);
	i = 0;
	while (s[i] && i < ft_strlen(s))
	{
		if (s[i] && s[i] != c)
		{
			lenword = i;
			while (s[lenword] != c && s[lenword])
				lenword++;
			split[j++] = ft_substr(s, i, lenword - i);
			i += lenword - i;
		}
		i++;
	}
	split[j] = NULL;
	return (split);
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

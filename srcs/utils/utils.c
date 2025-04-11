/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:10:30 by lefoffan          #+#    #+#             */
/*   Updated: 2025/04/11 11:10:42 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//same as str_join, but add a char between s1 and s2
char	*ft_join_mid(char *s1, char slash, char *s2)
{
	char	*ptr;
	int		i;
	int		j;

	ptr = malloc((ft_strlen(s1) + 1 + ft_strlen(s2) + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = slash;
	i++;
	j = 0;
	while (s2[j])
	{
		ptr[i] = s2[j];
		i++;
		j++;
	}
	ptr[i] = '\0';
	return (ptr);
}

//add s2 after s1 
//and free(s1)
//(kind of realloc)
char	*ft_straddstr(char *s1, char *s2)
{
	char	*res;

	if (s1 == NULL)
	{
		if (s2 == NULL)
			return (NULL);
		res = ft_strdup(s2);
		return (res);
	}
	else
	{
		res = ft_strjoin(s1, s2);
		free(s1);
		return (res);
	}
}

//add a char at the end of s1 (kind of realloc)
char	*ft_straddchar(char *str, char c)
{
	char	*res;
	int		i;

	if (!str)
	{
		res = ft_calloc(sizeof(char), 2);
		if (!res)
			return (NULL);
		res[0] = c;
		return (res);
	}
	res = ft_calloc(sizeof(char), ft_strlen(str) + 2);
	if (!res)
		return (NULL);
	i = -1;
	while (str[++i])
		res[i] = str[i];
	res[i] = c;
	i++;
	free(str);
	return (res);
}

void	free_db_array(char **arr)
{
	int	i;

	if (arr)
	{
		i = 0;
		while (arr[i])
		{
			free(arr[i]);
			i++;
		}
		free(arr);
	}
}

//* Return number of occurences
int	find_occurences(char *str, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

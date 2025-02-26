#include "minishell.h"

void	ft_execve(char *path, char **arg)
{
	if (execve(path, arg, NULL) == -1)
	{
		free(path);
		free_db_array(arg);
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

char	*ft_strjoin_middle(char const *s1, char slash, char const *s2)
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

char	*ft_stradd(char *s1, char *s2)
{
	char	*res;

	if (s1 == NULL)
	{
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

char	*ft_add_end_space(char *str)
{
	char	*res;
	int		i;

	res = malloc((ft_strlen(str) + 2) * sizeof(char));
	i = 0;
	while (str[i])
	{
		res[i] = str[i];
		i++;
	}
	res[i] = ' ';
	i++;
	res[i] = '\0';
	free(str);
	return (res);
}

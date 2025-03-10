#include "../minishell.h"

int	check_quote(char *str)
{
	int	i;
	int	quote;

	quote = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
			quote++;
		i++;
	}
	return (quote);
}

//return lines until right number of auotes are provided
char	*get_lines(char *line)
{
	char	*new_line;
	char	*temp;
	char	*res;

	new_line = readline(">");
	res = ft_join_mid(line, '\n', new_line);
	while (check_quote(new_line) % 2 == 0)
	{
		temp = ft_strdup(res);
		free(res);
		new_line = readline(">");
		res = ft_join_mid(temp, '\n', new_line);
		free(temp);
	}
	free(new_line);
	return (res);
}

//find s2 in s1
int	ft_strfind(char *s1, char *s2)
{
	int	i;
	int	j;
	int	s2_size;

	i = 0;
	s2_size = ft_strlen(s2);
	while (s1[i])
	{
		j = 0;
		if (s1[i] == s2[j])
		{
			while (s1[i] == s2[j])
			{
				j++;
				i++;
			}
			if (j == s2_size)
				return (1);
		}
		else
			i++;
	}
	return (0);
}

//return the size of a 2D array
int	double_arr_len(char **arr)
{
	int	size;

	size = 0;
	while (arr[size])
		size++;
	return (size);
}

char	**prepare_line(char *line)
{
	char	**arr;
	char	**res;
	int		i;

	arr = ft_split(line, "|");
	i = 0;
	while (arr[i])
		i++;
	res = malloc((i + 1) * sizeof(char *));
	i = 0;
	while (arr[i])
	{
		res[i] = ft_strtrim(arr[i], " ");
		i++;
	}
	res[i] = NULL;
	free_db_array(arr);
	return (res);
}

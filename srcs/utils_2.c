#include "minishell.h"

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

char	*get_lines(char *line)
{
	char	*new_line;
	char	*temp;
	char	*res;
	// int		i;

	// i = 0;
	new_line = readline(">");
	res = ft_strjoin_middle(line, '\n', new_line);
	while (check_quote(new_line) % 2 == 0)
	{
		temp = ft_strdup(res);
		free(res);
		new_line = readline(">");
		res = ft_strjoin_middle(temp, '\n', new_line);
		free(temp);
	}
	free(new_line);
	return (res);
}

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

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

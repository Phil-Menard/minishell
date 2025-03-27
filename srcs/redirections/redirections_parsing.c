#include "../minishell.h"

int	count_angle_brackets(char *line)
{
	int	count;
	int	i;

	count = 0;
	i = -1;
	while (line[++i])
	{
		if (line[i] == '>')
		{
			i++;
			if (line[i] == '>')
				i++;
			if (line[i] != ' ')
				count++;
		}
		else if (line[i] == '<')
		{
			i++;
			if (line[i] == '<')
				i++;
			if (line[i] != ' ')
				count++;
		}
	}
	return (count);
}

char	*fill_redir_line(char *line, char *res, int i, int j)
{
	while (line[i])
	{
		if (line[i] == '>')
		{
			res[j++] = line[i++];
			if (line[i] == '>')
				res[j++] = line[i++];
			if (line[i] != ' ')
				res[j++] = ' ';
		}
		else if (line[i] == '<')
		{
			res[j++] = line[i++];
			if (line[i] == '<')
				res[j++] = line[i++];
			if (line[i] != ' ')
				res[j++] = ' ';
		}
		else
			res[j++] = line[i++];
	}
	res[j] = '\0';
	return (res);
}

char	*parse_redirections(char *line)
{
	char	*res;
	int		count;
	int		i;
	int		j;

	res = NULL;
	count = count_angle_brackets(line);
	if (count == 0)
		return (ft_strdup(line));
	res = malloc((ft_strlen(line) + count + 1) * sizeof(char));
	i = 0;
	j = 0;
	res = fill_redir_line(line, res, i, j);
	return (res);
}

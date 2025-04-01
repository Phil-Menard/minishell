#include "../minishell.h"

// cat <<1  << 2 << 3 < Makefile << 4 < out << 5 > 6 << 7
// 123457
static char	**getdel(char *line)
{
	char	**split;
	char	**tmp;
	size_t	i;

	split = ft_split(line, "<<");
	if (!split)
		return (NULL);
	i = -1;
	while (split[++i])
	{
		tmp = ft_split(split[i], " ");
		if (!tmp)
			return (NULL);
		free(split[i]);
		split[i] = ft_strdup(tmp[0]);
		if (!split[i])
			return (NULL);
		free_db_array(tmp);
	}
	return (split);
}

static void	add(char *res, char *line)
{
	res = ft_straddstr(res, line);
	res = ft_straddchar(res, '\n');
}

void	heredoc(char *str)
{
	char	*res;
	char	**split;
	char	*line;
	int		fd;
	int		i;

	fd = open(HEREDOC, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	i = 1;
	res = NULL;
	split = getdel(str);
	while (split[i])
	{
		line = readline(">");
		if (ft_strlen(line) == ft_strlen(split[i]))
		{
			if (ft_strncmp(line, split[i], ft_strlen(line)) == 0)
				i++;
			else if (i > (double_arr_len(split) - 2))
				add(res, line);
		}
		else if (i > (double_arr_len(split) - 2))
			add(res, line);
		free(line);
	}
	ft_putstr_fd(res, fd);
	close(fd);
	free(res); //tmp
	free_db_array(split);
}

char	*trunc_heredoc(char *line)
{
	char	*res;
	char	**split;
	size_t	i;

	i = 0;
	res = NULL;
	split = ft_split(line, " ");
	if (!split)
		return (NULL);
	while (line[i])
	{
		if (split[i + 1] && split[i + 2] && ft_strfind(split[i + 1], "<<"))
			i += 2;
		res = ft_straddstr(res, split[i]);
		i++;
	}
	free(line);
	printf("res : %s\n", res);
	return (res);
}

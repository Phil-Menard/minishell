#include "minishell.h"

int	is_redirected(char *str)
{
	if (strrchr(str, '<') != NULL && strrchr(str, '>') != NULL)
		return (0);
	else if (strrchr(str, '<') != NULL && strrchr(str, '>') == NULL)
		return (1);
	else if (strrchr(str, '<') == NULL && strrchr(str, '>') != NULL)
		return (2);
	else
		return (-1);
}

char	*str_without_redir(char *str)
{
	char	**arr;
	char	*res;
	int		i;

	arr = ft_split(str, ' ');
	i = 0;
	res = NULL;
	while (arr[i])
	{
		if (ft_strrchr(arr[i], '<') == NULL && ft_strrchr(arr[i], '>') == NULL)
		{
			if (res)
				res = ft_add_end_space(res);
			res = ft_stradd(res, arr[i]);
		}
		else
			i++;
		if (arr[i] != NULL)
			i++;
	}
	free_db_array(arr);
	return (res);
}

char	*get_infile(char *str)
{
	char	**arr;
	char	*res;
	int		i;

	arr = ft_split(str, ' ');
	i = 0;
	res = NULL;
	while (arr[i])
	{
		if (ft_strrchr(arr[i], '<') != NULL)
		{
			i++;
			res = ft_strdup(arr[i]);
			free_db_array(arr);
			return (res);
		}
		i++;
	}
	free_db_array(arr);
	free(str);
	return (res);
}

char	*get_outfile(char *str)
{
	char	**arr;
	char	*res;
	int		i;

	arr = ft_split(str, ' ');
	i = 0;
	res = NULL;
	while (arr[i])
	{
		if (ft_strrchr(arr[i], '>') != NULL)
		{
			i++;
			res = ft_strdup(arr[i]);
			free_db_array(arr);
			return (res);
		}
		i++;
	}
	free_db_array(arr);
	free(str);
	return (res);
}

void	prepare_redir(char *str, int redirection)
{
	char	*path;
	char	**arg;
	char	*line;
	int		pipefd[2];

	line = str_without_redir(str);
	path = get_right_path(line);
	arg = fill_arg(path, line);
	free(line);
	if (pipe(pipefd) == -1)
		return (perror("pipe"), exit(EXIT_FAILURE));
	if (redirection == 0)
		redir_in_and_out(str, pipefd, path, arg);
	else if (redirection == 1)
		redir_input(str, pipefd, path, arg);
	else if (redirection == 2)
		redir_output(str, pipefd, path, arg);
	close(pipefd[0]);
	close(pipefd[1]);
	free_db_array(arg);
	free(path);
}

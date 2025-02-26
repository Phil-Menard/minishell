#include "minishell.h"

int	is_redirected(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '<')
			return (1);
		i++;
	}
	return (0);
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
		if (ft_strrchr(arr[i], '<') == NULL)
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
	free(str);
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

void	redir_input(int *pipefd, int infile, char *path, char **arg)
{
	int	id;

	id = fork();
	if (id == 0)
	{
		pipefd[0] = infile;
		close(pipefd[1]);
		if (dup2(pipefd[0], STDIN_FILENO) == -1)
			exit(EXIT_FAILURE);
		close(pipefd[0]);
		ft_execve(path, arg);
	}
	else
	{
		wait(NULL);
		close(pipefd[0]);
		close(pipefd[1]);
		close(infile);
		free_db_array(arg);
		free(path);
	}
}

void	prepare_redir(char *str)
{
	char	*path;
	char	**arg;
	int		pipefd[2];
	int		infile;

	infile = open(get_infile(str), O_RDONLY);
	if (infile == -1)
		perror(get_infile(str));
	str = str_without_redir(str);
	path = get_right_path(str);
	arg = fill_arg(path, str);
	if (pipe(pipefd) == -1)
		return (perror("pipe"), exit(EXIT_FAILURE));
	redir_input(pipefd, infile, path, arg);
}

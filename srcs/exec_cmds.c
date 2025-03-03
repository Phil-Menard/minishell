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

//PREPARE DOUBLE ARRAY FOR EXECVE
char	**fill_arg(char *path, char *argv)
{
	char	**arg;

	if (!path)
		return (NULL);
	arg = ft_split(argv, ' ');
	free(arg[0]);
	arg[0] = ft_strdup(path);
	return (arg);
}

char	*get_next_path(char *arr, char *str)
{
	char	*path;
	char	*cmd;
	char	**args;

	if (ft_strrchr(str, '/') != NULL)
	{
		args = ft_split(str, ' ');
		cmd = ft_strdup(args[0]);
		free_db_array(args);
		if (access(cmd, X_OK) != 0)
		{
			ft_putstr_fd(str, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			exit(EXIT_FAILURE);
		}
		return (cmd);
	}
	args = ft_split(str, ' ');
	cmd = ft_strdup(args[0]);
	free_db_array(args);
	path = ft_strjoin_middle(arr, '/', cmd);
	free(cmd);
	return (path);
}

//FIND CORRECT PATH TO EXECUTE CMD
char	*get_right_path(char *str)
{
	int		i;
	char	*path;
	char	**arr;

	i = 0;
	arr = ft_split(getenv("PATH"), ':');
	i = 0;
	while (arr[i])
	{
		path = get_next_path(arr[i], str);
		if (access(path, X_OK) == 0)
		{
			free_db_array(arr);
			return (path);
		}
		free(path);
		i++;
	}
	free_db_array(arr);
	return (NULL);
}

void	exec_cmds(char *str, int *fd)
{
	char	*path;
	char	**arg;
	int		id;
	int		redirection;

	redirection = is_redirected(str);
	if (redirection >= 0)
		prepare_redir(str, redirection, fd);
	else
	{
		path = get_right_path(str);
		arg = fill_arg(path, str);
		id = fork();
		if (id == 0)
			ft_execve(path, arg);
		else
		{
			wait(NULL);
			free_db_array(arg);
			free(path);
		}
	}
}

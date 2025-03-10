#include "../minishell.h"

char	**lst_to_arr(t_env **env)
{
	t_env	*current;
	char	**arr;
	int		size;
	int		i;

	current = *env;
	size = env_size(*env);
	arr = malloc((size + 1) * sizeof(char *));
	i = 0;
	while (current)
	{
		arr[i] = ft_strdup(current->var);
		i++;
		current = current->next;
	}
	arr[i] = NULL;
	return (arr);
}

void	ft_execve(char *path, char **arg, t_env **env)
{
	char	**arr_env;

	arr_env = lst_to_arr(env);
	if (execve(path, arg, arr_env) == -1)
	{
		if (path)
			free(path);
		if (arg)
			free_db_array(arg);
		if (arr_env)
			free_db_array(arr_env);
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

//prepare double array for execve
char	**fill_arg(char *path, char *argv)
{
	char	**arg;

	if (!path)
		return (NULL);
	arg = ft_split(argv, " ");
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
		args = ft_split(str, " ");
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
	args = ft_split(str, " ");
	cmd = ft_strdup(args[0]);
	free_db_array(args);
	path = ft_join_mid(arr, '/', cmd);
	free(cmd);
	return (path);
}

//find correct path to execute cmd
char	*get_right_path(char *str)
{
	int		i;
	char	*path;
	char	**arr;

	i = 0;
	arr = ft_split(getenv("PATH"), ":");
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

void	exec_cmds(char *str, int *fd, int id, t_env **env)
{
	char	*path;
	char	**arg;
	int		redirection;

	redirection = is_redirected(str);
	if (redirection >= 0)
		prepare_redir(str, redirection, fd, id, env);
	else
	{
		path = get_right_path(str);
		arg = fill_arg(path, str);
		if (id == 0)
			exec_redir(path, arg, fd, id, env);
		id = fork();
		if (id == 0)
			ft_execve(path, arg, env);
		else
		{
			wait(NULL);
			if (path)
				free(path);
			if (arg)
				free_db_array(arg);
		}
	}
}

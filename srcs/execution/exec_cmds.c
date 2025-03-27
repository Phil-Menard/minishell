#include "../minishell.h"

//prepare double array for execve
char	**fill_arg(char *path, char *line)
{
	char	**arg;

	if (!path)
		return (NULL);
	arg = NULL;
	arg = ft_split(line, " ");
	free(arg[0]);
	arg[0] = ft_strdup(path);
	return (arg);
}

char	*get_next_path(char *arr, char *str, t_var *vars)
{
	char	*path;

	if (ft_strrchr(str, '/') != NULL)
	{
		if (access(str, X_OK) != 0)
		{
			ft_putstr_fd(str, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			vars->exit_statut = 127;
		}
		return (str);
	}
	path = ft_join_mid(arr, '/', str);
	return (path);
}

//set arr variable for get_right_path
char	**set_arr(t_env **env)
{
	char	**arr;
	char	*temp;

	arr = NULL;
	temp = NULL;
	temp = ft_getenv(*env, "PATH");
	if (temp)
		arr = ft_split(temp, ":");
	free(temp);
	return (arr);
}

//find correct path to execute cmd
char	*get_right_path(char *str, t_var *vars, t_env **env)
{
	char	**arr;
	char	**split_cmd;
	char	*path;
	int		i;

	arr = set_arr(env);
	split_cmd = ft_split(str, " ");
	vars->cmd = ft_strdup(split_cmd[0]);
	free_db_array(split_cmd);
	i = 0;
	while (arr && arr[i])
	{
		path = get_next_path(arr[i], vars->cmd, vars);
		if (access(path, X_OK) == 0)
		{
			free_db_array(arr);
			return (path);
		}
		else if (ft_strrchr(vars->cmd, '/') != NULL)
			break ;
		free(path);
		i++;
	}
	vars->exit_statut = 127;
	if (ft_strrchr(vars->cmd, '/') == NULL)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	if (arr)
		free_db_array(arr);
	return (NULL);
}

void	exec_cmds(t_var *vars, int *fd, t_env **env, t_env **export)
{
	int		redirection;
	int		id;

	redirection = is_redirected(vars->line);
	if (redirection >= 0)
		prepare_redir(vars, fd, env, export);
	else
	{
		vars->path = get_right_path(vars->line, vars, env);
		if (vars->path)
		{
			vars->arg = fill_arg(vars->path, vars->line);
			id = fork();
			if (id == 0)
				ft_execve(vars, env, export, fd);
			else
				waitpid(id, &vars->exit_statut, 0);
		}
	}
}

#include "../minishell.h"

//prepare double array for execve
char	**fill_arg(t_var *vars)
{
	if (!vars->path)
		return (NULL);
	free(vars->cmd_line[0].args[0]);
	vars->cmd_line[0].args[0] = ft_strdup(vars->path);
	return (vars->cmd_line[0].args);
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
			return (NULL);
		}
		path = ft_strdup(str);
		return (path);
	}
	path = ft_join_mid(arr, '/', str);
	return (path);
}

//find correct path to execute cmd
char	*get_right_path(char *str, t_var *vars, t_env **env)
{
	char	**arr;
	char	*path;
	int		i;

	arr = split_path_var(env);
	i = 0;
	while (arr && arr[i])
	{
		path = get_next_path(arr[i], str, vars);
		if (path && access(path, X_OK) == 0)
		{
			free_db_array(arr);
			return (path);
		}
		else if (ft_strrchr(str, '/') != NULL)
			break ;
		free(path);
		i++;
	}
	end_right_path(vars, str, arr);
	return (NULL);
}

void	exec_cmds(t_var *vars, int *fd, t_env **env, t_env **export)
{
	// int		redirection;
	int		id;

	// redirection = is_redirected(vars->line);
	// if (redirection >= 0)
	// 	prepare_redir(vars, fd, env, export);
	// else
	// {
	vars->path = get_right_path(vars->cmd_line[0].cmd, vars, env);
	if (vars->path)
	{
		vars->cmd_line[0].args = fill_arg(vars);
		id = fork();
		if (id == 0)
			ft_execve(vars, env, export, fd);
		else
		{
			waitpid(id, &vars->exit_statut, 0);
			if (WIFEXITED(vars->exit_statut))
				vars->exit_statut = WEXITSTATUS(vars->exit_statut);
		}
	}
	// }
}

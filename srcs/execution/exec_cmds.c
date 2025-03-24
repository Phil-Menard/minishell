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

void	ft_execve(t_var *vars, t_env **env, t_env **export, int *fd)
{
	char	**arr_env;

	arr_env = lst_to_arr(env);
	if (vars->arg == NULL || execve(vars->path, vars->arg, arr_env) == -1)
	{
		free_and_close(vars, env, export, fd);
		if (arr_env)
			free_db_array(arr_env);
		exit(2);
	}
}

//check which cmd is entered in vars, and call a builtin or execve
void	builtin_or_cmd(t_var *vars, int *fd, t_env **env, t_env **exp)
{
	vars->cmd_split = ft_split(vars->content, " ");
	vars->size_cmd = ft_strlen(vars->cmd_split[0]);
	if (ft_strncmp(vars->cmd_split[0], "pwd", vars->size_cmd) == 0)
		ft_pwd(vars, fd[1]);
	else if (ft_strncmp(vars->content, "env", vars->size_cmd) == 0)
		ft_env(*env, vars, fd[1]);
	else if (ft_strncmp(vars->content, "echo", vars->size_cmd) == 0)
		ft_echo(vars->content, fd[1]);
	else if (ft_strncmp(vars->content, "cd", vars->size_cmd) == 0)
		ft_cd(vars->content, env, fd[1]);
	else if (ft_strncmp(vars->content, "unset", vars->size_cmd) == 0)
		ft_unset(vars->content, env, exp);
	else if (ft_strncmp(vars->content, "export", vars->size_cmd) == 0)
		ft_export(vars, env, exp, fd[1]);
	else if (ft_strncmp(vars->content, "exit", vars->size_cmd) == 0)
		ft_exit(fd, vars, env, exp);
	else if (ft_strncmp(vars->content, "$?", vars->size_cmd) == 0)
	{
		ft_putstr_fd(ft_itoa(vars->exit_statut), fd[1]);
		ft_putstr_fd("\n", fd[1]);
	}
	else
		exec_cmds(vars, fd, env, exp);
	close_multiple_fd(fd);
	free_db_array(vars->cmd_split);
}

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

	unblock_sigquit = 1;
	arr_env = lst_to_arr(env);
	if (vars->arg == NULL || execve(vars->path, vars->arg, arr_env) == -1)
	{
		free_and_close(vars, env, export, fd);
		if (arr_env)
			free_db_array(arr_env);
		vars->exit_statut = 2;
		exit(vars->exit_statut);
	}
}

//check which cmd is entered in vars, and call a builtin or execve
void	builtin_or_cmd(t_var *vars, int *fd, t_env **env, t_env **exp)
{
	vars->cmd_split = ft_split(vars->line, " ");
	if (ft_cmpstr(vars->cmd_split[0], "pwd") == 0)
		ft_pwd(vars, fd[1]);
	else if (ft_cmpstr(vars->cmd_split[0], "env") == 0)
		ft_env(*env, vars, fd[1]);
	else if (ft_cmpstr(vars->cmd_split[0], "echo") == 0)
		ft_echo(vars->line, fd[1], vars);
	else if (ft_cmpstr(vars->cmd_split[0], "cd") == 0)
		ft_cd(vars->line, env, fd[1], vars);
	else if (ft_cmpstr(vars->cmd_split[0], "unset") == 0)
		ft_unset(vars->line, env, exp, vars);
	else if (ft_cmpstr(vars->cmd_split[0], "export") == 0)
		ft_export(vars, env, exp, fd[1]);
	else if (ft_cmpstr(vars->cmd_split[0], "exit") == 0)
		ft_exit(fd, vars, env, exp);
	else
		exec_cmds(vars, fd, env, exp);
	close_multiple_fd(fd);
	update_exit_env(*env, vars);
}

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
	in_child = 1;
	set_signal_action();
	if (execve(vars->path, vars->cmd_line[vars->i].args, arr_env) == -1)
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
	if (ft_cmpstr(vars->cmd_line[vars->i].cmd, "pwd") == 0)
		ft_pwd(vars, fd[1]);
	else if (ft_cmpstr(vars->cmd_line[vars->i].cmd, "env") == 0)
		ft_env(*env, vars, fd[1]);
	else if (ft_cmpstr(vars->cmd_line[vars->i].cmd, "echo") == 0)
		ft_echo(vars, fd[1]);
	else if (ft_cmpstr(vars->cmd_line[vars->i].cmd, "cd") == 0)
		ft_cd(env, fd[1], vars);
	else if (ft_cmpstr(vars->cmd_line[vars->i].cmd, "unset") == 0)
		ft_unset(env, exp, vars);
	else if (ft_cmpstr(vars->cmd_line[vars->i].cmd, "export") == 0)
		ft_export(vars, env, exp, fd[1]);
	else if (ft_cmpstr(vars->cmd_line[vars->i].cmd, "exit") == 0)
		ft_exit(fd, vars, env, exp);
	else
		exec_cmds(vars, fd, env, exp);
	close_multiple_fd(fd);
	update_exit_env(*env, vars);
}

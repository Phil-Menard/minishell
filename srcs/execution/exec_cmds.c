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
		ft_putstr_fd(vars->content, 1);
		ft_putstr_fd(": command not found\n", 1);
		free_and_close(vars, env, export, fd);
		if (arr_env)
			free_db_array(arr_env);
		exit(EXIT_FAILURE);
	}
}

//check which cmd is entered in vars, and call a builtin or execve
void	builtin_or_cmd(t_var *vars, int *fd, t_env **env, t_env **exp)
{
	int	size;

	vars->cmd_split = ft_split(vars->content, " ");
	size = ft_strlen(vars->cmd_split[0]);
	if (ft_strncmp(vars->cmd_split[0], "pwd", size) == 0)
		ft_pwd(fd[1]);
	else if (ft_strncmp(vars->content, "env", size) == 0)
		ft_env(*env, fd[1]);
	else if (ft_strncmp(vars->content, "echo", size) == 0)
		ft_echo(vars->content, fd[1]);
	else if (ft_strncmp(vars->content, "cd", size) == 0)
		ft_cd(vars->content, *env, fd[1]);
	else if (ft_strncmp(vars->content, "unset", size) == 0)
		ft_unset(vars->content, env, exp);
	else if (ft_strncmp(vars->content, "export", size) == 0)
		ft_export(vars->content, env, exp, fd[1]);
	else if (ft_strncmp(vars->content, "exit", size) == 0)
		ft_exit(fd, vars, env, exp);
	else
		exec_cmds(vars, fd, env, exp);
	close_multiple_fd(fd);
	free_db_array(vars->cmd_split);
}

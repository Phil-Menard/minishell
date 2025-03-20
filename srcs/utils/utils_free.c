#include "../minishell.h"

void	free_vars(t_var *vars)
{
	free_db_array(vars->cmd_split);
	if (vars->arg)
	{
		free_db_array(vars->arg);
		vars->arg = NULL;
	}
	if (vars->content)
	{
		free(vars->content);
		vars->content = NULL;
	}
	if (vars->prompt)
		free(vars->prompt);
	if (vars->arr)
	{
		free_db_array(vars->arr);
		vars->arr = NULL;
	}
	if (vars->cmd_pipe)
	{
		free(vars->cmd_pipe);
		vars->cmd_pipe = NULL;
	}
}

void	free_and_close(t_var *vars, t_env **env, t_env **exp, int *fd)
{
	close_multiple_fd(fd);
	free_vars(vars);
	free_env(*env);
	free_env(*exp);
}

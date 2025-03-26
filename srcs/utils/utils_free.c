#include "../minishell.h"

void	free_vars(t_var *vars)
{
	if (vars->cmd_split != NULL)
		free_db_array(vars->cmd_split);
	if (vars->arg)
	{
		free_db_array(vars->arg);
		vars->arg = NULL;
	}
	if (vars->line)
	{
		free(vars->line);
		vars->line = NULL;
	}
	if (vars->prompt)
		free(vars->prompt);
	if (vars->arr)
	{
		free_db_array(vars->arr);
		vars->arr = NULL;
	}
	if (vars->path)
		free(vars->path);
}

void	free_and_close(t_var *vars, t_env **env, t_env **exp, int *fd)
{
	close_multiple_fd(fd);
	free_vars(vars);
	free_env(*env);
	free_env(*exp);
}

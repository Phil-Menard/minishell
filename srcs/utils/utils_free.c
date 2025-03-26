#include "../minishell.h"

void	nullify_arg_vars(t_var *vars)
{
	vars->arg = NULL;
	vars->arr = NULL;
	vars->cmd = NULL;
	vars->cmd_split = NULL;
	vars->line = NULL;
	vars->path = NULL;
	vars->pids = NULL;
	vars->prompt = NULL;
}

void	free_vars(t_var *vars)
{
	if (vars->cmd_split != NULL)
		free_db_array(vars->cmd_split);
	if (vars->arg)
		free_db_array(vars->arg);
	if (ft_strrchr(vars->line, '/') != NULL)
		free(vars->cmd);
	if (vars->line)
		free(vars->line);
	if (vars->prompt)
		free(vars->prompt);
	if (vars->arr)
		free_db_array(vars->arr);
	if (vars->path && vars->cmd)
	{
		free(vars->path);
		free(vars->cmd);
	}
	if (!vars->path && vars->cmd)
		free(vars->cmd);
	nullify_arg_vars(vars);
}

void	init_vars(t_var *vars)
{
	nullify_arg_vars(vars);
	vars->exit_statut = 0;
	vars->i = 0;
	vars->size_cmd = 0;
}

void	free_and_close(t_var *vars, t_env **env, t_env **exp, int *fd)
{
	close_multiple_fd(fd);
	free_vars(vars);
	free_env(*env);
	free_env(*exp);
}

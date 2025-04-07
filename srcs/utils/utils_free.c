#include "../minishell.h"

//set all variables with char * or char ** to NULL
void	nullify_arg_vars(t_var *vars)
{
	vars->cmd_line = NULL;
	// vars->cmd_line->infile = NULL;
	// vars->cmd_line->outfile = NULL;
	vars->line = NULL;
	vars->path = NULL;
	vars->pids = NULL;
	vars->prompt = NULL;
}

//free all variables from t_var and set them to NULL
void	free_vars(t_var *vars)
{
	size_t	i;

	if (vars->prompt)
		free(vars->prompt);
	i = 0;
	while (i < vars->nb_cmd_line)
	{
		free_db_array(vars->cmd_line[i].args);
		free(vars->cmd_line[i].cmd);
		i++;
	}
	free(vars->cmd_line);
	if (vars->line)
		free(vars->line);
	if (vars->path)
		free(vars->path);
	nullify_arg_vars(vars);
}

//set all variables in t_var to NULL or 0
void	init_vars(t_var *vars)
{
	nullify_arg_vars(vars);
	vars->exit_statut = 0;
	vars->i = 0;
}

void	free_and_close(t_var *vars, t_env **env, t_env **exp, int *fd)
{
	close_multiple_fd(fd);
	free_vars(vars);
	free_env(*env);
	free_env(*exp);
}

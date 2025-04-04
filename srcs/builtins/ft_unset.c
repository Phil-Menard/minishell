#include "../minishell.h"

void	ft_unset(t_env **env, t_env **export, t_var *vars)
{
	int		i;
	int		size;

	size = ft_strlen("declare -x ");
	i = 1;
	while (vars->cmd_line[0].args[i])
	{
		*env = remove_env_var(env, vars->cmd_line[0].args[i], 0);
		*export = remove_env_var(export, vars->cmd_line[0].args[i], size);
		i++;
	}
	vars->exit_statut = 0;
}

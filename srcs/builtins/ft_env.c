#include "../minishell.h"

void	ft_env(t_env *env, t_var *vars, int fd)
{
	while (env != NULL)
	{
		if (ft_strncmp(env->var, "?", 1) == 0)
			env = env->next;
		else
		{
			ft_putstr_fd(env->var, fd);
			ft_putchar_fd('\n', fd);
			env = env->next;
		}
	}
	vars->exit_statut = 0;
}

void	update_exit_env(t_env *env, t_var *vars)
{
	char	*temp;

	temp = NULL;
	temp = ft_itoa(vars->exit_statut);
	modify_env(env, "?", temp);
	free(temp);
}

#include "../minishell.h"

void	ft_env(t_env *env, t_var *vars, int fd)
{
	while (env != NULL)
	{
		ft_putstr_fd(env->var, fd);
		ft_putchar_fd('\n', fd);
		env = env->next;
	}
	vars->exit_statut = 0;
}

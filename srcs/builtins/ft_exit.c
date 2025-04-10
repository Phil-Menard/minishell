#include "../minishell.h"

void	free_before_exit(int *fd, t_var *vars, t_env **env, t_env **export)
{
	rl_clear_history();
	close_multiple_fd(fd);
	free_env(*env);
	free_env(*export);
	free_vars(vars);
	ft_putstr_fd("exit\n", 1);
}

void	arg_not_numeric(int *fd, t_var *vars, t_env **env, t_env **export)
{
	ft_putstr_fd("minishell: exit: ", 1);
	ft_putstr_fd(vars->cmd_line[vars->i].cmd, 1);
	ft_putstr_fd(": numeric argument required\n", 1);
	vars->exit_statut = 2;
	free_before_exit(fd, vars, env, export);
	exit(vars->exit_statut);
}

long	set_nb_exit(int *fd, t_var *vars, t_env **env, t_env **export)
{
	long int	nb;
	char		*content;
	int			i;

	i = 0;
	while (vars->cmd_line[vars->i].args[1][i] == '0')
		i++;
	nb = ft_atol(vars->cmd_line[vars->i].args[1] + i);
	content = ft_ltoa(nb);
	if (ft_strncmp(vars->cmd_line[vars->i].args[1] + i, content,
			ft_strlen(vars->cmd_line[vars->i].args[1] + i)) != 0)
	{
		if (ft_strncmp(vars->cmd_line[vars->i].args[1], "-9223372036854775808",
				ft_strlen(vars->cmd_line[vars->i].args[1])) != 0)
		{
			free(content);
			arg_not_numeric(fd, vars, env, export);
		}
	}
	free(content);
	if (nb < 0)
		vars->exit_statut = -((-nb) % 256);
	else
		vars->exit_statut = nb % 256;
	return (vars->exit_statut);
}

void	too_many_args(t_var *vars, t_env **env)
{
	ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 1);
	vars->exit_statut = 1;
	update_exit_env(*env, vars);
}

void	ft_exit(int *fd, t_var *vars, t_env **env, t_env **export)
{
	long	nb;
	int		i;

	nb = 0;
	if (vars->cmd_line[vars->i].args[1]
		&& ft_str_isalpha(vars->cmd_line[vars->i].args[1]) == 0
		&& vars->cmd_line[vars->i].args[2])
		too_many_args(vars, env);
	else
	{
		if (vars->cmd_line[vars->i].args[1])
		{
			i = -1;
			while (vars->cmd_line[vars->i].args[1][++i])
			{
				if (ft_isalpha(vars->cmd_line[vars->i].args[1][i]) == 1)
					arg_not_numeric(fd, vars, env, export);
			}
			nb = set_nb_exit(fd, vars, env, export);
		}
		update_exit_env(*env, vars);
		free_before_exit(fd, vars, env, export);
		exit(nb);
	}
}

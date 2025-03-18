#include "../minishell.h"

void	free_before_exit(int *fd, t_var *vars, t_env **env, t_env **export)
{
	rl_clear_history();
	close_multiple_fd(fd);
	free_env(*env);
	free_env(*export);
	if (vars->content)
		free(vars->content);
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
	else
		ft_putstr_fd("exit\n", 1);
}

void	arg_not_numeric(int *fd, t_var *vars, t_env **env, t_env **export)
{
	free_before_exit(fd, vars, env, export);
	ft_putstr_fd("minishell: exit: ", 1);
	ft_putstr_fd(vars->cmd_split[1], 1);
	ft_putstr_fd(": numeric argument required\n", 1);
	if (vars->cmd_split)
		free_db_array(vars->cmd_split);
	exit(2);
}

long	set_nb_exit(int *fd, t_var *vars, t_env **env, t_env **export)
{
	long int	nb;
	char		*content;

	nb = ft_atol(vars->cmd_split[1]);
	content = ft_ltoa(nb);
	if (ft_strncmp(vars->cmd_split[1], content,
			ft_strlen(vars->cmd_split[1])) != 0)
	{
		if (ft_strncmp(vars->cmd_split[1], "-9223372036854775808",
				ft_strlen(vars->cmd_split[1])) != 0)
		{
			free(content);
			arg_not_numeric(fd, vars, env, export);
		}
	}
	free(content);
	if (nb < 0)
		nb = -((-nb) % 256);
	else
		nb = nb % 256;
	return (nb);
}

void	ft_exit(int *fd, t_var *vars, t_env **env, t_env **export)
{
	long	nb;
	int		i;

	nb = 0;
	if (vars->cmd_split[1] && ft_str_isalpha(vars->cmd_split[1]) == 0
		&& vars->cmd_split[2])
		ft_putstr_fd("minishell: exit: too many arguments\n", 1);
	else
	{
		if (vars->cmd_split[1])
		{
			i = -1;
			while (vars->cmd_split[1][++i])
			{
				if (ft_isalpha(vars->cmd_split[1][i]) == 1)
					arg_not_numeric(fd, vars, env, export);
			}
			nb = set_nb_exit(fd, vars, env, export);
		}
		if (vars->cmd_split)
			free_db_array(vars->cmd_split);
		free_before_exit(fd, vars, env, export);
		exit(nb);
	}
}

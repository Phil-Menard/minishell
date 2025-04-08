#include "../minishell.h"

void	echo_loop(t_var *vars, int fd, int option)
{
	int	i;
	int	j;

	if (option == 1)
		j = 2;
	else
		j = 1;
	while (vars->cmd_line[vars->i].args[j])
	{
		i = 0;
		while (vars->cmd_line[vars->i].args[j][i])
		{
			ft_putchar_fd(vars->cmd_line[vars->i].args[j][i], fd);
			i++;
		}
		ft_putchar_fd(' ', fd);
		j++;
	}
	if (option == 0)
		ft_putchar_fd('\n', fd);
}

//check if arg is only -n (multiple n can be written) or different
int	check_arg(char *str)
{
	int	i;

	if (!str)
		return (0);
	if (str[0] != '-')
		return (0);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (i);
}

void	ft_echo(t_var *vars, int fd)
{
	int		j;
	int		option;

	option = 0;
	j = check_arg(vars->cmd_line[vars->i].args[1]);
	if (j > 0)
		option = 1;
	echo_loop(vars, fd, option);
	vars->exit_statut = 0;
}

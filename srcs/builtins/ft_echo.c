#include "../minishell.h"

// void	handle_var(char *str, int *x, int fd)
// {
// 	char	*var;
// 	char	*res;
// 	int		i;
// 	int		j;

// 	i = *x;
// 	j = 0;
// 	while (str[i] != '\0' && str[i] != ' ' && str[i] != '"' && str[i] != '\n')
// 	{
// 		j++;
// 		i++;
// 	}
// 	var = ft_substr(str, *x, j);
// 	*x = i - 1;
// 	res = getenv(var);
// 	if (res)
// 		ft_putstr_fd(res, fd);
// 	free(var);
// }

void	echo_loop(t_var *vars, int i, int fd, int option)
{
	int	j;

	j = 1;
	while (vars->cmd_line[0].args[j])
	{
		ft_putchar_fd(vars->cmd_line[0].args[j][i], fd);
		i++;
	}
	if (option == 0)
		ft_putchar_fd('\n', fd);
}

//check if arg is only -n (multiple n can be written) or different
int	check_arg(char *str)
{
	int	i;

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
	// char	*line;
	int		i;
	int		j;
	int		option;

	option = 0;
	j = check_arg(vars->cmd_line[0].args[1]);
	if (j > 0)
	{
		i = 6 + j;
		option = 1;
	}
	else
		i = 5;
	//line = str_without_redir(str);
	echo_loop(vars, i, fd, option);
	// free(line);
	vars->exit_statut = 0;
}

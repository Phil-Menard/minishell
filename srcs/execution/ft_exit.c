#include "../minishell.h"

void	free_before_exit(int *fd, t_line *line, t_env **env, t_env **export)
{
	rl_clear_history();
	close_multiple_fd(fd);
	free_env(*env);
	free_env(*export);
	if (line->content)
		free(line->content);
	if (line->prompt)
		free(line->prompt);
	if (line->arr)
	{
		free_db_array(line->arr);
		line->arr = NULL;
	}
	if (line->cmd_pipe)
	{
		free(line->cmd_pipe);
		line->cmd_pipe = NULL;
	}
	else
		ft_putstr_fd("exit\n", 1);
}

void	arg_not_numeric(int *fd, t_line *line, t_env **env, t_env **export)
{
	free_before_exit(fd, line, env, export);
	ft_putstr_fd("minishell: exit: ", 1); 
	ft_putstr_fd(line->cmd_split[1], 1);
	ft_putstr_fd(": numeric argument required\n", 1);
	if (line->cmd_split)
		free_db_array(line->cmd_split);
	exit(2);
}

long	set_nb_exit(int *fd, t_line *line, t_env **env, t_env **export)
{
	long int	nb;
	char		*content;

	nb = ft_atol(line->cmd_split[1]);
	content = ft_ltoa(nb);
	if (ft_strncmp(line->cmd_split[1], content, 
		ft_strlen(line->cmd_split[1])) != 0)
	{
		if (ft_strncmp(line->cmd_split[1], "-9223372036854775808", 
		ft_strlen(line->cmd_split[1])) != 0)
		{
			free(content);
			arg_not_numeric(fd, line, env, export);
		}
	}
	free(content);
	if (nb < 0)
		nb = -((-nb) % 256);
	else
		nb = nb % 256;
	return (nb);
}

void	ft_exit(int *fd, t_line *line, t_env **env, t_env **export)
{
	long	nb;
	int		i;

	nb = 0;
	if (line->cmd_split[1] && ft_str_isalpha(line->cmd_split[1]) == 0
		&& line->cmd_split[2])
		ft_putstr_fd("minishell: exit: too many arguments\n", 1);
	else
	{
		if (line->cmd_split[1])
		{
			i = -1;
			while(line->cmd_split[1][++i])
			{
				if (ft_isalpha(line->cmd_split[1][i]) == 1)
					arg_not_numeric(fd, line, env, export);
			}
			nb = set_nb_exit(fd, line, env, export);
		}
		if (line->cmd_split)
			free_db_array(line->cmd_split);
		free_before_exit(fd, line, env, export);
		exit(nb);
	}
}
//9223372036854775807 => longest int possible for exit, otherwise
//it returns this error : 
//"bash: exit: 9223372036854775808: numeric argument required"

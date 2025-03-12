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

void	ft_exit(int *fd, t_line *line, t_env **env, t_env **export)
{
	int	i;

	i = ft_atoi(line->cmd_split[1]);
	i = i % 256;
	if (line->cmd_split[1])
	{
		i = 0;
		while(line->cmd_split[1][i])
		{
			if (ft_isalpha(line->cmd_split[1][i]) == 1)
				arg_not_numeric(fd, line, env, export);
			i++;
		}
	}
	else
	{
		if (line->cmd_split)
			free_db_array(line->cmd_split);
		free_before_exit(fd, line, env, export);
		printf("%d\n", i);
		exit(EXIT_SUCCESS);
	}
}
//9223372036854775807 => longest int possible for exit, otherwise
//it returns this error : 
//"bash: exit: 9223372036854775808: numeric argument required"

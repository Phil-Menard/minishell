#include "minishell.h"

void	print_minishell(void)
{
	printf("___  ________ _   _ _____ _____ _   _  _____ _      _     \n");
	printf("|  \\/  |_   _| \\ | |_   _/  ___| | | ||  ___| |    | |    \n");
	printf("| .  . | | | |  \\| | | | \\ `--.| |_| || |__ | |    | |    \n");
	printf("| |\\/| | | | | . ` | | |  `--. \\  _  ||  __|| |    | |    \n");
	printf("| |  | |_| |_| |\\  |_| |_/\\__/ / | | || |___| |____| |____\n");
	printf("\\_|  |_/\\___/\\_| \\_/\\___/\\");
	printf("____/\\_| |_/\\____/\\_____/\\_____/\n\n");
}

void	builtin_or_cmd(char *line, int *fd, t_env **env)
{
	if (ft_strncmp(line, "pwd", 3) == 0)
		ft_pwd(fd[1]);
	else if (ft_strncmp(line, "env", 3) == 0)
		ft_env(*env, fd[1]);
	else if (ft_strncmp(line, "echo", 4) == 0)
		ft_echo(line, fd[1]);
	else if (ft_strncmp(line, "cd", 2) == 0)
		ft_cd(line, *env, fd[1]);
	else if (ft_strncmp(line, "unset", 5) == 0)
		ft_unset(line, env);
	else if (ft_strncmp(line, "exit", 4) == 0)
	{
		close_multiple_fd(fd);
		ft_exit();
	}
	else
		exec_cmds(line, fd, env);
}

// verifie si il y a un pipe 
void	check_pipes(char *line, t_env **env)
{
	pid_t	*pids;
	char	**arr;
	int		*fd;
	int		arr_size;

	arr = prepare_line(line);
	fd = NULL;
	if (!arr[1])
	{
		fd = init_fd();
		fd = set_fd(line, fd);
		builtin_or_cmd(line, fd, env);
	}
	else
	{
		arr_size = double_arr_len(arr);
		pids = malloc(sizeof(pid_t) * arr_size);
		pipex(arr, env, arr_size, pids);
	}
	free_db_array(arr);
	free(fd);
}

char	*set_prompt_arg(void)
{
	char	*prompt_arg;
	char	*user_name;
	char	*pwd;
	char	*dollar_sign;

	user_name = getenv("USER");
	dollar_sign = ft_strdup("$ ");
	prompt_arg = ft_strjoin(user_name, ":");
	pwd = getcwd(NULL, 0);
	prompt_arg = ft_straddstr(prompt_arg, pwd);
	prompt_arg = ft_straddstr(prompt_arg, dollar_sign);
	free(dollar_sign);
	free(pwd);
	return (prompt_arg);
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
	char	*line;
	char	*prompt_arg;

	(void) argc;
	(void) argv;
	env = NULL;
	fill_env(&env, envp);
	print_minishell();
	while (1)
	{
		prompt_arg = set_prompt_arg();
		line = readline(prompt_arg);
		add_history(line);
		if (ft_strlen(line) > 0)
			ft_parse(line, env); //* pour parser
		free(line);
		free(prompt_arg);
	}
	free_env(env);
	rl_clear_history();
	return (0);
}

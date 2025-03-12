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

//check which cmd is entered in line, and call a builtin or execve
void	builtin_or_cmd(t_line *line, int *fd, t_env **env, t_env **export)
{
	line->cmd_split = ft_split(line->content, " ");
	if (ft_strncmp(line->cmd_split[0], "pwd", ft_strlen(line->cmd_split[0])) == 0)
		ft_pwd(fd[1]);
	else if (ft_strncmp(line->content, "env", ft_strlen(line->cmd_split[0])) == 0)
		ft_env(*env, fd[1]);
	else if (ft_strncmp(line->content, "echo", ft_strlen(line->cmd_split[0])) == 0)
		ft_echo(line->content, fd[1]);
	else if (ft_strncmp(line->content, "cd", ft_strlen(line->cmd_split[0])) == 0)
		ft_cd(line->content, *env, fd[1]);
	else if (ft_strncmp(line->content, "unset", ft_strlen(line->cmd_split[0])) == 0)
		ft_unset(line->content, env, export);
	else if (ft_strncmp(line->content, "export", ft_strlen(line->cmd_split[0])) == 0)
		ft_export(line->content, env, export, fd[1]);
	else if (ft_strncmp(line->content, "exit", ft_strlen(line->cmd_split[0])) == 0)
	{
		ft_exit(fd, line, env, export);
	}
	else
		exec_cmds(line->content, fd, env);
	free_db_array(line->cmd_split);
}

//check if line contains a pipe or not, and call the corresponding function
void	check_pipes(t_line *line, t_env **env, t_env **export)
{
	int		*fd;
	int		arr_size;

	fd = NULL;
	line->cmd_pipe = NULL;
	line->arr = prepare_line(line->content);
	if (!line->arr[1])
	{
		if (ft_strncmp(line->arr[0], "exit", 4) == 0)
		{
			free_db_array(line->arr);
			line->arr = NULL;
		}
		fd = init_fd();
		fd = set_fd(line->content, fd);
		builtin_or_cmd(line, fd, env, export);
	}
	else
	{
		arr_size = double_arr_len(line->arr);
		pipex(line, env, export, arr_size);
	}
	if (line->arr)
		free_db_array(line->arr);
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
	t_env	*export;
	t_line	line;

	(void) argc;
	(void) argv;
	env = NULL;
	export = NULL;
	fill_env(&env, envp);
	init_export_lst(&env, &export);
	print_minishell();
	while (1)
	{
		line.prompt = set_prompt_arg();
		line.content = readline(line.prompt);
		add_history(line.content);
		if (ft_strlen(line.content) > 0)
			check_pipes(&line, &env, &export);
			// ft_parse(line, env);
			// builtins(line, env, &exit_code);
		free(line.content);
		free(line.prompt);
	}
	free_env(env);
	free_env(export);
	rl_clear_history();
	return (0);
}

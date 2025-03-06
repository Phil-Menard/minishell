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

void	find_correct_function(char *line, int *fd, t_env **env, int id)
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
		exec_cmds(line, fd, id);
	if (id == 0)
		exit(EXIT_SUCCESS);
}

void	builtins(char *line, t_env **env)
{
	char	**arr;
	int		*fd;
	int		i;

	fd = init_fd();
	arr = prepare_line(line);
	i = 0;
	if (!arr[1])
	{
		fd = set_fd(line, fd);
		find_correct_function(arr[i], fd, env, -1);
	}
	else
		pipex(arr, env, fd);
	free_db_array(arr);
	close_multiple_fd(fd);
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
			ft_execute(line, &env); // *fonction qui va appeler tout le reste
			// builtins(line, env, &exit_code);
		free(line);
		free(prompt_arg);
	}
	free_env(env);
	rl_clear_history();
	return (0);
}

/*
work on mybranch (Leon || Phil)
push with git push origin mybranch
go to main (git checkout main)
update main (git pull origin main)
fusion branch (git merge mybranch)
push everything (git push origin main)
*/

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
		ft_pwd(fd);
	else if (ft_strncmp(line, "env", 3) == 0)
		ft_env(*env, fd);
	else if (ft_strncmp(line, "echo", 4) == 0)
		ft_echo(line, fd);
	else if (ft_strncmp(line, "cd", 2) == 0)
		ft_cd(line, *env, fd);
	else if (ft_strncmp(line, "unset", 5) == 0)
		ft_unset(line, env);
	else if (ft_strncmp(line, "exit", 4) == 0)
	{
		close_multiple_fd(fd);
		ft_exit();
	}
	else
		exec_cmds(line, fd, id);
}

/*
pipefd[0] = fd[0] 
	if fd[0] = 1 > input is keyboard
	if fd[0] > 1 > input is file
pipefd[1] = fd[1] or fd[2]
	if fd[1] > 1 et fd[2] == 1 => outfile is trunc mode
	if fd[1] == 1 et fd[2] > 1 => outfile is append mode
	if fd[1] == 1 et fd[2] == 1 => outfile is terminal
		and should be send to brother if not last child
*/
void	exec_cmds_bis(char *str, int infile, int outfile)
{
	char	*path;
	char	**arg;
	
	path = get_right_path(str);
	arg = fill_arg(path, str);
	if (dup2(infile, STDIN_FILENO) == -1)
	{
		perror("infile");
		exit(EXIT_FAILURE);
	}
	close(infile);
	if (outfile != 1)
	{
		if (dup2(outfile, STDOUT_FILENO) == -1)
		{
			perror("outfile");
			exit(EXIT_FAILURE);
		}
		close(outfile);
	}
	if (execve(path, arg, NULL) == -1)
	{
		if (path)
			free(path);
		if (arg)
			free_db_array(arg);
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

/* void	find_correct_function_bis(char *line, int infile, int outfile, t_env **env)
{
	if (ft_strncmp(line, "pwd", 3) == 0)
		ft_pwd(&outfile);
	else if (ft_strncmp(line, "env", 3) == 0)
		ft_env(*env, &outfile);
	else if (ft_strncmp(line, "echo", 4) == 0)
		ft_echo(line, &outfile);
	else if (ft_strncmp(line, "cd", 2) == 0)
		ft_cd(line, *env, &outfile);
	else if (ft_strncmp(line, "unset", 5) == 0)
		ft_unset(line, env);
	else if (ft_strncmp(line, "exit", 4) == 0)
	{
		ft_exit();
	}
	else
		exec_cmds_bis(line, infile, outfile);
} */

/* void	exec_cmds(int previous_fd, int next_fd, char *argv, char **env)
{
	char	*path;
	char	**arg;

	if (dup2(previous_fd, STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
	close(previous_fd);
	if (dup2(next_fd, STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	close(next_fd);
	path = get_right_path(env, argv);
	arg = fill_arg(path, argv);
	if (execve(path, arg, NULL) == -1)
	{
		free(path);
		free_db_array(arg);
		perror("execve");
		exit(EXIT_FAILURE);
	}
} */

void	pipex(char **arr, t_env **env, int *fd)
{
	int		pipefd[2];
	int		i;
	pid_t	id;

	(void) env;
	i = 0;
	while (arr[i])
	{
		if (pipe(pipefd) == -1)
			return (perror("pipe"), exit(EXIT_FAILURE));
		id = fork();
		if (id == -1)
			return (perror("fork"), exit(EXIT_FAILURE));
		if (id == 0)
		{
			pipefd[0] = fd[0];
			if (i == double_arr_len(arr) - 1)
				pipefd[1] = fd[1];
			exec_cmds_bis(arr[i], pipefd[0], pipefd[1]);
		}
		fd[0] = pipefd[0];
		close(pipefd[1]);
		wait(NULL);
		i++;
	}
	close(pipefd[0]);
}

void	builtins(char *line, t_env **env)
{
	char	**arr;
	int		*fd;
	int		i;

	fd = init_fd();
	arr = prepare_line(line);
	i = 0;
	fd = set_fd(line, fd);
	if (!arr[1])
	{
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

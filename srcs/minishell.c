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

int	*check_redir(char *line, int *fd)
{
	int		redirection;
	char	*infile;
	char	*outfile;

	infile = get_infile(line);
	outfile = get_outfile(line);
	redirection = is_redirected(line);
	if (redirection == 0)
	{
		fd[0] = open(infile, O_RDONLY);
		fd[1] = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	else if (redirection == 1)
		fd[0] = open(infile, O_RDONLY);
	else if (redirection == 2)
		fd[1] = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redirection == 3)
		fd[3] = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	return (fd);
}

void	builtins(char *line, char **env, int *exit_code)
{
	int	*fd;
	int	i;

	fd = malloc(3 * sizeof(int));
	i = -1;
	while (++i < 3)
		fd[i] = 1;
	fd = check_redir(line, fd);
	if (ft_strncmp(line, "pwd", 3) == 0)
		ft_pwd();
	else if (ft_strncmp(line, "env", 3) == 0)
		ft_env(env);
	else if (ft_strncmp(line, "echo", 4) == 0)
		ft_echo(line);
	else if (ft_strncmp(line, "cd", 2) == 0)
		ft_cd(line);
	else if (ft_strncmp(line, "exit", 4) == 0)
	{
		close_multiple_fd(fd);
		ft_exit(exit_code);
	}
	else
		exec_cmds(line, fd);
	close_multiple_fd(fd);
	free(fd);
}

char	*set_prompt_arg()
{
	char	*prompt_arg;
	char	*user_name;
	char	*pwd;
	char	*dollar_sign;

	user_name = getenv("USER");;
	dollar_sign = ft_strdup("$ ");
	prompt_arg = ft_strjoin(user_name, ":");
	pwd = getcwd(NULL, 0);
	prompt_arg = ft_straddstr(prompt_arg, pwd);
	prompt_arg = ft_straddstr(prompt_arg, dollar_sign);
	free(pwd);
	free(dollar_sign);
	return (prompt_arg);
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	char	*prompt_arg;
	int		exit_code;

	(void) argc;
	(void) argv;
	print_minishell();
	exit_code = 1;
	while (exit_code == 1)
	{
		prompt_arg = set_prompt_arg();
		line = readline(prompt_arg);
		if (ft_strlen(line) > 0)
			ft_execute(line, env, &exit_code); // *fonction qui va appeler tout le reste
			// builtins(line, env, &exit_code);
	}
	free(prompt_arg);
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

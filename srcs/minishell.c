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

void	builtins(char *line, char **env, int *exit_code)
{
	if (ft_strncmp(line, "pwd", 3) == 0)
		ft_pwd(); // print actual working
	else if (ft_strncmp(line, "env", 3) == 0)
		ft_env(env); // print the env
	else if (ft_strfind(line, "echo") == 1)
		ft_echo(line);
	else if (ft_strncmp(line, "cd", 2) == 0)
		ft_cd(line);
	else if (ft_strncmp(line, "exit", 4) == 0)
		ft_exit(exit_code);
	else
		exec_cmds(line);
}

char	*set_prompt_arg(char *user_name)
{
	char	*prompt_arg;
	char	*pwd;
	char	*dollar_sign;

	dollar_sign = ft_strdup("$ ");
	prompt_arg = ft_strjoin(user_name, ":");
	pwd = getcwd(NULL, 0);
	prompt_arg = ft_stradd(prompt_arg, pwd);
	prompt_arg = ft_stradd(prompt_arg, dollar_sign);
	free(pwd);
	free(dollar_sign);
	return (prompt_arg);
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	char	*user_name;
	char	*prompt_arg;
	int		exit_code;

	(void) argc;
	(void) argv;
	(void) env;
	print_minishell();
	exit_code = 1;
	line = NULL;
	user_name = getenv("USER");
	while (exit_code == 1)
	{
		prompt_arg = set_prompt_arg(user_name);
		line = readline(prompt_arg);
		if (ft_strlen(line) > 0)
		{
			if (check_quote(line) % 2 != 0)
				line = get_lines(line);
			builtins(line, env, &exit_code);
		}
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

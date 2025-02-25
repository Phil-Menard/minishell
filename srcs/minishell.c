#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*line;

	(void) argc;
	(void) argv;
	(void) env;
	line = NULL;
	while (ft_strncmp(line, "exit", 4) != 0)
	{
		line = readline(">");
		if (ft_strncmp(line, "pwd", 3) == 0)
			ft_pwd(); // print actual working
		if (ft_strncmp(line, "env", 3) == 0)
			ft_env(env); // print the env
		if (ft_strncmp(line, "echo", 4) == 0)
			ft_echo(line); // print the env
	}
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

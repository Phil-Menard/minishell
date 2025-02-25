#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*line;

	(void) argc;
	(void) argv;

	line = readline(">");
	printf("%s\n", line);
	ft_pwd(); // print actual working
	ft_env(env); // print the env
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

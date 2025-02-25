#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*line;

	line = readline(">");
	printf("%s\n", line);
	(void) argc;
	(void) argv;
	ft_pdw();
	ft_env(env);
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

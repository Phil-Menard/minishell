#include "minishell.h"

int	main(void)
{
	char	*line;

	line = readline(">");
	printf("%s\n", line);
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

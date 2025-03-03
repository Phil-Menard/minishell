#include "minishell.h"

//EXECVE WITH CORRECT REDIRECTION
void	exec_redir(char *path, char **arg, int *fd)
{
	int	id;

	id = fork();
	if (id == 0)
	{
		if (fd[0] != 1)
		{
			if (dup2(fd[0], STDIN_FILENO) == -1)
				exit(EXIT_FAILURE);
		}
		if (fd[1] != 1)
		{
			if (dup2(fd[1], STDOUT_FILENO) == -1)
				exit(EXIT_FAILURE);
		}
		if (fd[2] != 1)
		{
			if (dup2(fd[2], STDOUT_FILENO) == -1)
				exit(EXIT_FAILURE);
		}
		ft_execve(path, arg);
	}
	else
		wait(NULL);
}

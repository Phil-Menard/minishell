#include "../minishell.h"

//execve with correct redirection
void	exec_redir(char *path, char **arg, int *fd, int id)
{
	if (id != 0)
		id = fork();
	if (id == 0)
	{
		if (dup2(fd[0], STDIN_FILENO) == -1)
			exit(EXIT_FAILURE);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			exit(EXIT_FAILURE);
		ft_execve(path, arg);
	}
	else
		wait(NULL);
}

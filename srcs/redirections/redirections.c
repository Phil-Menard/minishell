#include "../minishell.h"

//execve with correct redirection
void	exec_redir(char *path, char **arg, int *fd, int id)
{
	if (id != 0)
		id = fork();
	if (id == 0)
	{
		if (dup2(fd[0], STDIN_FILENO) == -1)
		{
			perror("infile");
			exit(EXIT_FAILURE);
		}
		close(fd[0]);
		if (fd[1] != 1)
		{
			if (dup2(fd[1], STDOUT_FILENO) == -1)
			{
				perror("outfile");
				exit(EXIT_FAILURE);
			}
			close(fd[1]);
		}
		ft_execve(path, arg);
	}
	else
		wait(NULL);
}

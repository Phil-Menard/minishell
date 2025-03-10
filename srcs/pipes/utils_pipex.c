#include "../minishell.h"

void	close_previous_fd(int previous_fd)
{
	if (previous_fd != -1)
		close(previous_fd);
}

void	wait_childs(pid_t *pids, int arr_size)
{
	int		j;

	j = 0;
	while (j < arr_size)
	{
		waitpid(pids[j], NULL, 0);
		j++;
	}
	free(pids);
}

void	outfile_dups(int *fd, int *pipefd, int i, int arr_size)
{
	if (fd[1] != 1)
		dup2(fd[1], STDOUT_FILENO);
	else if (i < arr_size - 1)
		dup2(pipefd[1], STDOUT_FILENO);
}

void	post_cmd(int *pipefd, int *previous_fd, int *fd)
{
	close(pipefd[1]);
	close_previous_fd(*previous_fd);
	*previous_fd = pipefd[0];
	close_multiple_fd(fd);
}

void	end_pipex(int *pipefd, pid_t *pids, int arr_size, int previous_fd)
{
	close(pipefd[0]);
	wait_childs(pids, arr_size);
	close_previous_fd(previous_fd);
}

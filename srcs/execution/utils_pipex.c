#include "../minishell.h"

void	close_previous_fd(int previous_fd)
{
	if (previous_fd != -1)
		close(previous_fd);
}

//wait for every child processes to finish
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

//regroups dups2 in pipex
void	outfile_dups(int *fd, int *pipefd, int i, int arr_size)
{
	if (fd[1] != 1)
		dup2(fd[1], STDOUT_FILENO);
	else if (i < arr_size - 1)
		dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
}

//regroups every functions called after child process
void	post_cmd(int *pipefd, int *previous_fd, int *fd)
{
	close(pipefd[1]);
	close_previous_fd(*previous_fd);
	*previous_fd = pipefd[0];
	close_multiple_fd(fd);
}

//regroups every functions called at the end of pipex
void	end_pipex(int *pipefd, pid_t *pids, int arr_size, int prev_fd)
{
	close(pipefd[0]);
	wait_childs(pids, arr_size);
	close_previous_fd(prev_fd);
}

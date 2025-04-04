#include "../minishell.h"

void	close_previous_fd(int previous_fd)
{
	if (previous_fd != -1)
		close(previous_fd);
}

//wait for every child processes to finish
void	wait_childs(t_var *vars)
{
	size_t	j;

	j = 0;
	while (j < vars->nb_cmd_line)
	{
		waitpid(vars->pids[j], &vars->exit_statut, 0);
		if (WIFEXITED(vars->exit_statut))
			vars->exit_statut = WEXITSTATUS(vars->exit_statut);
		j++;
	}
}

//regroups dups2 in pipex
void	outfile_dups(int *fd, int *pipefd, t_var *vars)
{
	if (fd[1] != 1)
		dup2(fd[1], STDOUT_FILENO);
	else if (vars->i < vars->nb_cmd_line - 1)
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
void	end_pipex(int *pipefd, t_var *vars, int prev_fd)
{
	close(pipefd[0]);
	wait_childs(vars);
	free(vars->pids);
	close_previous_fd(prev_fd);
}

#include "../minishell.h"

void	exec_cmds_bis(char *str, int id, int *pipefd)
{
	char	*path;
	char	**arg;
	char	*line;

	close(pipefd[0]);
	close(pipefd[1]);
	line = str_without_redir(str);
	path = get_right_path(line);
	arg = fill_arg(path, line);
	if (id == 0)
		ft_execve(path, arg);
	else
	{
		if (path)
			free(path);
		if (arg)
			free_db_array(arg);
		if (line)
			free(line);
	}
}

void	pipe_and_fork(int *pipefd, int *pids)
{
	if (pipe(pipefd) == -1)
		return (perror("pipe"), exit(EXIT_FAILURE));
	*pids = fork();
	if (*pids == -1)
		return (perror("fork"), exit(EXIT_FAILURE));
}

void	pipex(char **arr, t_env **env, int arr_size, pid_t *pids)
{
	int		pipefd[2];
	int		*fd;
	int		previous_fd;
	int		i;

	(void)env;
	previous_fd = -1;
	i = -1;
	while (arr[++i])
	{
		fd = init_and_set_fd(arr[i]);
		previous_fd = set_previous_fd(fd, previous_fd);
		pipe_and_fork(pipefd, &pids[i]);
		if (pids[i] == 0)
		{
			if (previous_fd != -1)
				dup2(previous_fd, STDIN_FILENO);
			outfile_dups(fd, pipefd, i, arr_size);
			close_previous_fd(previous_fd);
			exec_cmds_bis(arr[i], pids[i], pipefd);
			exit(EXIT_SUCCESS);
		}
		post_cmd(pipefd, &previous_fd, fd);
	}
	end_pipex(pipefd, pids, arr_size, previous_fd);
}

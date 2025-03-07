#include "../minishell.h"

void	exec_cmds_bis(char *str, int id)
{
	char	*path;
	char	**arg;
	char	*line;

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

void	pipex(char **arr, t_env **env)
{
	int		pipefd[2];
	int		*fd;
	int		previous_fd;
	int		i;
	int		j;
	int		n;
	pid_t	*pids;

	(void)env;
	n = double_arr_len(arr);
	pids = malloc(sizeof(pid_t) * n);
	i = 0;
	previous_fd = -1;
	while (arr[i])
	{
		fd = init_fd();
		fd = set_fd(arr[i], fd);
		previous_fd = set_previous_fd(fd, previous_fd);
		if (pipe(pipefd) == -1)
			return (perror("pipe"), exit(EXIT_FAILURE));
		pids[i] = fork();
		if (pids[i] == -1)
			return (perror("fork"), exit(EXIT_FAILURE));
		if (pids[i] == 0)
		{
			if (previous_fd != -1)
				dup2(previous_fd, STDIN_FILENO);
			if (fd[1] != 1)
				dup2(fd[1], STDOUT_FILENO);
			else if (i < n - 1)
				dup2(pipefd[1], STDOUT_FILENO);
			if (previous_fd != -1)
				close(previous_fd);
			close(pipefd[0]);
			close(pipefd[1]);
			exec_cmds_bis(arr[i], pids[i]);
			exit(EXIT_SUCCESS);
		}
		close(pipefd[1]);
		if (previous_fd != -1)
			close(previous_fd);
		previous_fd = pipefd[0];
		close_multiple_fd(fd);
		i++;
	}
	close(pipefd[0]);
	j = 0;
	while (j < n)
	{
		waitpid(pids[j], NULL, 0);
		j++;
	}
	free(pids);
	if (previous_fd != -1)
		close(previous_fd);
}

/* void	pipex(char **arr, t_env **env, int *fd)
{
	int		pipefd[2];
	int		previous_fd;
	int		i;
	pid_t	id;

	i = 0;
	while (arr[i])
	{
		fd = init_fd();
		fd = set_fd(arr[i], fd);
		previous_fd = set_previous_fd(fd, i, previous_fd);
		if (pipe(pipefd) == -1)
			return (perror("pipe"), exit(EXIT_FAILURE));
		id = fork();
		if (id == -1)
			return (perror("fork"), exit(EXIT_FAILURE));
		if (id == 0)
		{
			pipefd[0] = previous_fd;
			if (i == double_arr_len(arr) - 1 || fd[1] != 1)
				pipefd[1] = fd[1];
			find_correct_function(arr[i], pipefd, env, id);
		}
		wait(NULL);
		previous_fd = pipefd[0];
		close(pipefd[1]);
		close_multiple_fd(fd);
		i++;
	}
	close(pipefd[0]);
} */

/* char	*get_cmd_name(char *argv)
{
	char	**arr;
	char	*cmd;

	arr = ft_split(argv, " ");
	cmd = ft_strdup(arr[0]);
	free_db_array(arr);
	return (cmd);
} */

/* void	check_path_errors(char *argv, char **env, int *pipefd)
{
	char	*path;

	close(*pipefd);
	path = get_right_path(env, argv);
	if (!path)
	{
		path = get_cmd_name(argv);
		ft_putstr_fd(path, 2);
		free(path);
		ft_putstr_fd(": command not found\n", 2);
		free_db_array(argv);
		exit(EXIT_FAILURE);
	}
} */

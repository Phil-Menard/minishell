#include "../minishell.h"

void	exec_cmds_bis(char *str, t_env **env)
{
	char	*path;
	char	**arg;
	char	*line;

	line = str_without_redir(str);
	path = get_right_path(line);
	arg = fill_arg(path, line);
	ft_execve(path, arg, env);
}

void	find_correct_function_bis(char *line, int *fd, int *pipefd, t_env **env)
{
	close(pipefd[0]);
	close(pipefd[1]);
	if (ft_strncmp(line, "pwd", 3) == 0)
		ft_pwd(fd[1]);
	else if (ft_strncmp(line, "env", 3) == 0)
		ft_env(*env, fd[1]);
	else if (ft_strncmp(line, "echo", 4) == 0)
		ft_echo(line, fd[1]);
	else if (ft_strncmp(line, "cd", 2) == 0)
		ft_cd(line, *env, fd[1]);
	else if (ft_strncmp(line, "unset", 5) == 0)
		ft_unset(line, env);
	else if (ft_strncmp(line, "exit", 4) == 0)
	{
		close_multiple_fd(fd);
		ft_exit();
	}
	else
		exec_cmds_bis(line, env);
	exit(EXIT_SUCCESS);
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
			find_correct_function_bis(arr[i], fd, pipefd, env);
		}
		post_cmd(pipefd, &previous_fd, fd);
	}
	end_pipex(pipefd, pids, arr_size, previous_fd);
}

#include "../minishell.h"

//same as exec_cmd but for pipes
void	exec_cmds_pipes(t_line *line, t_env **env, t_env **export)
{
	char	*path;
	char	**arg;
	char	*cmd;

	cmd = str_without_redir(line->cmd_pipe);
	path = get_right_path(cmd);
	arg = fill_arg(path, cmd);
	free(line->cmd_pipe);
	line->cmd_pipe = NULL;
	free(line->content);
	free(line->prompt);
	free_db_array(line->arr);
	free(line->pids);
	free_env(*export);
	ft_execve(path, arg, env);
}

void	free_child_process(t_line *line, t_env **env, t_env **export)
{
	free(line->cmd_pipe);
	line->cmd_pipe = NULL;
	free(line->content);
	free(line->prompt);
	free_db_array(line->arr);
	free(line->pids);
	free_env(*export);
	free_env(*env);
}

//same as builtin_or_cmd but for pipes
void	builtin_or_cmd_pipes(t_line *line, int *fd, t_env **env, t_env **export)
{
	line->cmd_pipe = ft_strdup(line->arr[line->i]);
	line->cmd_split = ft_split(line->cmd_pipe, " ");
	if (ft_strncmp(line->cmd_split[0], "pwd", ft_strlen(line->cmd_split[0])) == 0)
		ft_pwd(fd[1]);
	else if (ft_strncmp(line->cmd_split[0], "env", ft_strlen(line->cmd_split[0])) == 0)
		ft_env(*env, fd[1]);
	else if (ft_strncmp(line->cmd_split[0], "echo", ft_strlen(line->cmd_split[0])) == 0)
		ft_echo(line->cmd_pipe, fd[1]);
	else if (ft_strncmp(line->cmd_split[0], "cd", ft_strlen(line->cmd_split[0])) == 0)
		ft_cd(line->cmd_pipe, *env, fd[1]);
	else if (ft_strncmp(line->cmd_split[0], "unset", ft_strlen(line->cmd_split[0])) == 0)
		ft_unset(line->cmd_pipe, env, export);
	else if (ft_strncmp(line->cmd_pipe, "export", ft_strlen(line->cmd_split[0])) == 0)
		ft_export(line->cmd_pipe, env, export, fd[1]);
	else if (ft_strncmp(line->cmd_split[0], "exit", ft_strlen(line->cmd_split[0])) == 0)
	{
		free_db_array(line->cmd_split);
		free(line->pids);
		ft_exit(fd, line, env, export);
	}
	else
		exec_cmds_pipes(line, env, export);
	free_db_array(line->cmd_split);
	close_multiple_fd(fd);
	free_child_process(line, env, export);
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

//modified pipex that redirects input and output in correct file descriptor/pipe
void	pipex(t_line *line, t_env **env, t_env **export, int arr_size)
{
	int		pipefd[2];
	int		*fd;
	int		previous_fd;

	line->pids = malloc(sizeof(pid_t) * arr_size);
	previous_fd = -1;
	line->i = -1;
	while (line->arr[++line->i])
	{
		fd = init_and_set_fd(line->arr[line->i]);
		previous_fd = set_previous_fd(fd, previous_fd);
		pipe_and_fork(pipefd, &line->pids[line->i]);
		if (line->pids[line->i] == 0)
		{
			if (previous_fd != -1)
				dup2(previous_fd, STDIN_FILENO);
			outfile_dups(fd, pipefd, line->i, arr_size);
			close_previous_fd(previous_fd);
			builtin_or_cmd_pipes(line, fd, env, export);
		}
		post_cmd(pipefd, &previous_fd, fd);
	}
	end_pipex(pipefd, line->pids, arr_size, previous_fd);
}

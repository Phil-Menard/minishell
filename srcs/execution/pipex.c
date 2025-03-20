#include "../minishell.h"

//same as exec_cmd but for pipes
void	exec_cmds_pipes(t_var *vars, t_env **env, t_env **export, int *fd)
{
	char	*cmd;

	cmd = str_without_redir(vars->cmd_pipe);
	vars->path = get_right_path(cmd);
	vars->arg = fill_arg(vars->path, cmd);
	free(cmd);
	if (vars->arg)
	{
		free(vars->cmd_pipe);
		vars->cmd_pipe = NULL;
		free(vars->content);
		free(vars->prompt);
		free_db_array(vars->arr);
		free_env(*export);
	}
	free(vars->pids);
	ft_execve(vars, env, export, fd);
}

void	free_child_process(t_var *vars, t_env **env, t_env **export)
{
	free(vars->cmd_pipe);
	vars->cmd_pipe = NULL;
	free(vars->content);
	free(vars->prompt);
	free_db_array(vars->arr);
	free(vars->pids);
	free_env(*export);
	free_env(*env);
}

//same as builtin_or_cmd but for pipes
void	builtin_or_cmd_pipes(t_var *vars, int *fd, t_env **env, t_env **export)
{
	vars->cmd_pipe = ft_strdup(vars->arr[vars->i]);
	vars->cmd_split = ft_split(vars->cmd_pipe, " ");
	vars->size_cmd = ft_strlen(vars->cmd_split[0]);
	if (ft_strncmp(vars->cmd_split[0], "pwd", vars->size_cmd) == 0)
		ft_pwd(fd[1]);
	else if (ft_strncmp(vars->cmd_split[0], "env", vars->size_cmd) == 0)
		ft_env(*env, fd[1]);
	else if (ft_strncmp(vars->cmd_split[0], "echo", vars->size_cmd) == 0)
		ft_echo(vars->cmd_pipe, fd[1]);
	else if (ft_strncmp(vars->cmd_split[0], "cd", vars->size_cmd) == 0)
		ft_cd(vars->cmd_pipe, env, fd[1]);
	else if (ft_strncmp(vars->cmd_split[0], "unset", vars->size_cmd) == 0)
		ft_unset(vars->cmd_pipe, env, export);
	else if (ft_strncmp(vars->cmd_pipe, "export", vars->size_cmd) == 0)
		ft_export(vars->cmd_pipe, env, export, fd[1]);
	else if (ft_strncmp(vars->cmd_split[0], "exit", vars->size_cmd) == 0)
	{
		free_db_array(vars->cmd_split);
		free(vars->pids);
		ft_exit(fd, vars, env, export);
	}
	else
		exec_cmds_pipes(vars, env, export, fd);
	free_db_array(vars->cmd_split);
	close_multiple_fd(fd);
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
void	pipex(t_var *vars, t_env **env, t_env **export, int arr_size)
{
	int		pipefd[2];
	int		*fd;
	int		previous_fd;

	vars->pids = malloc(sizeof(pid_t) * arr_size);
	previous_fd = -1;
	vars->i = -1;
	while (vars->arr[++vars->i])
	{
		fd = init_and_set_fd(vars->arr[vars->i]);
		previous_fd = set_previous_fd(fd, previous_fd);
		pipe_and_fork(pipefd, &vars->pids[vars->i]);
		if (vars->pids[vars->i] == 0)
		{
			if (previous_fd != -1)
				dup2(previous_fd, STDIN_FILENO);
			outfile_dups(fd, pipefd, vars->i, arr_size);
			close_previous_fd(previous_fd);
			builtin_or_cmd_pipes(vars, fd, env, export);
			free_child_process(vars, env, export);
			exit(EXIT_SUCCESS);
		}
		post_cmd(pipefd, &previous_fd, fd);
	}
	end_pipex(pipefd, vars->pids, arr_size, previous_fd);
}

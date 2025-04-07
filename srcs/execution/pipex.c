#include "../minishell.h"

void	free_child_process(t_var *vars, t_env **env, t_env **export)
{
	free(vars->pids);
	free_vars(vars);
	free_env(*export);
	free_env(*env);
}

//same as exec_cmd but for pipes
void	exec_cmds_pipes(t_var *vars, t_env **env, t_env **export, int *fd)
{
	vars->path = NULL;
	vars->path = get_right_path(vars->cmd_line[vars->i].cmd, vars, env);
	if (vars->path != NULL)
	{
		vars->cmd_line[vars->i].args = fill_arg(vars);
		free(vars->pids);
		vars->pids = NULL;
		ft_execve(vars, env, export, fd);
	}
}

//same as builtin_or_cmd but for pipes
void	builtin_or_cmd_pipes(t_var *vars, int *fd, t_env **env, t_env **export)
{
	if (ft_cmpstr(vars->cmd_line[vars->i].cmd, "pwd") == 0)
		ft_pwd(vars, fd[1]);
	else if (ft_cmpstr(vars->cmd_line[vars->i].cmd, "env") == 0)
		ft_env(*env, vars, fd[1]);
	else if (ft_cmpstr(vars->cmd_line[vars->i].cmd, "echo") == 0)
		ft_echo(vars, fd[1]);
	else if (ft_cmpstr(vars->cmd_line[vars->i].cmd, "cd") == 0)
		ft_cd(env, fd[1], vars);
	else if (ft_cmpstr(vars->cmd_line[vars->i].cmd, "unset") == 0)
		ft_unset(env, export, vars);
	else if (ft_cmpstr(vars->cmd_line[vars->i].cmd, "export") == 0)
		ft_export(vars, env, export, fd[1]);
	else if (ft_cmpstr(vars->cmd_line[vars->i].cmd, "exit") == 0)
	{
		free(vars->pids);
		ft_exit(fd, vars, env, export);
	}
	else
		exec_cmds_pipes(vars, env, export, fd);
	close_multiple_fd(fd);
	update_exit_env(*env, vars);
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
void	pipex(t_var *vars, t_env **env, t_env **export)
{
	int		pipefd[2];
	int		*fd;
	int		previous_fd;

	vars->pids = malloc(sizeof(pid_t) * vars->nb_cmd_line);
	previous_fd = -1;
	vars->i = -1;
	while (++vars->i < vars->nb_cmd_line)
	{
		fd = init_and_set_fd(&vars->cmd_line[vars->i], vars, env);
		previous_fd = set_previous_fd(fd, previous_fd);
		pipe_and_fork(pipefd, &vars->pids[vars->i]);
		if (vars->pids[vars->i] == 0)
		{
			if (previous_fd != -1)
				dup2(previous_fd, STDIN_FILENO);
			outfile_dups(fd, pipefd, vars);
			close_previous_fd(previous_fd);
			builtin_or_cmd_pipes(vars, fd, env, export);
			free_child_process(vars, env, export);
			exit(vars->exit_statut);
		}
		post_cmd(vars, pipefd, &previous_fd, fd);
	}
	end_pipex(pipefd, vars, previous_fd);
}

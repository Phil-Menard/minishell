/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmenard <pmenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:09:20 by lefoffan          #+#    #+#             */
/*   Updated: 2025/04/16 16:19:13 by pmenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//prepare double array for execve
char	**fill_arg(t_var *vars)
{
	if (!vars->path)
		return (NULL);
	free(vars->cmd_line[vars->i].args[0]);
	vars->cmd_line[vars->i].args[0] = ft_strdup(vars->path);
	return (vars->cmd_line[vars->i].args);
}

char	*get_next_path(char *arr, char *str, t_var *vars)
{
	char		*path;

	if (find_occurences(str, '/') != 0)
	{
		if (access(str, X_OK) != 0)
		{
			if (errno == EACCES)
				errno_error(vars);
			else
			{
				ft_putstr_fd(str, 2);
				ft_putstr_fd(": No such file or directory\n", 2);
				vars->exit_statut = 127;
			}
			return (NULL);
		}
		path = ft_strdup(str);
		return (path);
	}
	if (!arr)
		return (str);
	else
		path = ft_join_mid(arr, '/', str);
	return (path);
}

//find correct path to execute cmd
char	*get_right_path(char *str, t_var *vars, t_env **env)
{
	char	**arr;
	char	*path;
	int		i;

	arr = split_path_var(env);
	path = NULL;
	if (!arr)
		path = path_with_way(str, vars);
	if (path)
		return (path);
	i = -1;
	while (arr && arr[++i])
	{
		path = get_next_path(arr[i], str, vars);
		if (path && access(path, X_OK) == 0)
		{
			free_db_array(arr);
			return (path);
		}
		else if (ft_strrchr(str, '/') != NULL)
			break ;
		free(path);
	}
	end_right_path(vars, str, arr);
	return (NULL);
}

void	end_single_cmd(t_var *vars, int id)
{
	int	status;

	status = 0;
	waitpid(id, &status, 0);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
			write(2, "Quit (core dumped)\n", 20);
		vars->exit_statut = 128 + WTERMSIG(status);
	}
	else if (WIFEXITED(status))
		vars->exit_statut = WEXITSTATUS(status);
	if (g_exit_signal == 2)
		vars->exit_statut = 130;
}

void	exec_cmds(t_var *vars, int *fd, t_env **env, t_env **export)
{
	int	redir;
	int	id;

	redir = is_redirected(vars->cmd_line->infile, vars->cmd_line->outfile);
	if (redir >= 0)
		prepare_redir(vars, fd, env, export);
	else
	{
		vars->path = get_right_path(vars->cmd_line[vars->i].cmd, vars, env);
		if (vars->path)
		{
			g_exit_signal = 1;
			vars->cmd_line[vars->i].args = fill_arg(vars);
			id = fork();
			if (id == 0)
				ft_execve(vars, env, export, fd);
			else
				end_single_cmd(vars, id);
		}
	}
}

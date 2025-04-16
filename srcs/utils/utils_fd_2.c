/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_fd_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmenard <pmenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:10:19 by lefoffan          #+#    #+#             */
/*   Updated: 2025/04/16 17:09:01 by pmenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//create all outfiles, closes them except last one and return it
int	set_fd_out(int fd, char **outfile, int redir, t_var *vars)
{
	int		i;
	int		size;
	char	**split;

	i = -1;
	size = double_arr_len(outfile);
	while (outfile[++i])
	{
		split = ft_split(outfile[i], " ");
		if (redir < 3)
			fd = open(split[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			fd = open(split[1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1 && errno == EACCES)
		{
			ft_putstr_fd("Permission denied\n", 2);
			vars->exit_statut = 1;
			free_db_array(split);
			return (fd);
		}
		if (i < size - 1)
			close(fd);
		free_db_array(split);
	}
	return (fd);
}

int	set_fd_in(int fd, char **infile, t_var *vars)
{
	int		i;
	int		size;
	char	**split;

	i = -1;
	size = double_arr_len(infile);
	while (infile[++i])
	{
		split = ft_split(infile[i], " ");
		fd = open(split[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				ft_putstr_fd("Permission denied\n", 2);
			else
				ft_putstr_fd("No such file or directory\n", 2);
			vars->exit_statut = 1;
			free_db_array(split);
			return (fd);
		}
		if (i < size - 1)
			close(fd);
		free_db_array(split);
	}
	return (fd);
}

//fd[0] : input
//fd[1] : output
int	*set_fd(t_cmd_line *cmd_line, t_var *vars, t_env **env, int *fd)
{
	int		redir;

	redir = is_redirected(cmd_line->infile, cmd_line->outfile);
	if (redir == 1 || redir == 0)
	{
		fd[0] = set_fd_in(fd[0], cmd_line->infile, vars);
		if (fd[0] != -1 && redir == 0)
			fd[1] = set_fd_out(fd[1], cmd_line->outfile, redir, vars);
	}
	else if (redir == 2)
		fd[1] = set_fd_out(fd[1], cmd_line->outfile, redir, vars);
	else if (redir == 3)
		fd[1] = set_fd_out(fd[1], cmd_line->outfile, redir, vars);
	else if (redir == 4)
	{
		fd[0] = set_fd_in(fd[0], cmd_line->infile, vars);
		if (fd[0] != -1)
			fd[1] = set_fd_out(fd[1], cmd_line->outfile, redir, vars);
	}
	if (fd[0] == -1 || fd[1] == -1)
		update_exit_env(*env, vars);
	return (fd);
}

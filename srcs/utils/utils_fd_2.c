/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_fd_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:10:19 by lefoffan          #+#    #+#             */
/*   Updated: 2025/04/11 11:10:42 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//create all outfiles, closes them except last one and return it
int	set_fd_out(int fd, char **outfile, int redir)
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
		if (i < size - 1)
			close(fd);
		free_db_array(split);
	}
	return (fd);
}

int	set_fd_in(int fd, char **infile)
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
		if (fd < 0)
		{
			perror(split[1]);
			free_db_array(split);
			return (-1);
		}
		if (i < size - 1)
			close(fd);
		free_db_array(split);
	}
	return (fd);
}

int	*find_files(int *fd, char **infile, char **outfile, int redir)
{
	if (redir == 1 || redir == 0)
	{
		fd[0] = set_fd_in(fd[0], infile);
		if (fd[0] != -1 && redir == 0)
			fd[1] = set_fd_out(fd[1], outfile, redir);
	}
	else if (redir == 2)
		fd[1] = set_fd_out(fd[1], outfile, redir);
	else if (redir == 3)
		fd[1] = set_fd_out(fd[1], outfile, redir);
	else if (redir == 4)
	{
		fd[0] = set_fd_in(fd[0], infile);
		if (fd[0] != -1)
			fd[1] = set_fd_out(fd[1], outfile, redir);
	}
	return (fd);
}

//fd[0] : input
//fd[1] : output
int	*set_fd(t_cmd_line *cmd_line, t_var *vars, t_env **env, int *fd)
{
	int		redir;

	redir = is_redirected(cmd_line->infile, cmd_line->outfile);
	fd = find_files(fd, cmd_line->infile, cmd_line->outfile, redir);
	if (fd[0] == -1)
	{
		vars->exit_statut = 1;
		update_exit_env(*env, vars);
	}
	return (fd);
}

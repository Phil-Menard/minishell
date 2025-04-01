#include "../minishell.h"

//create all outfiles, closes them except last one and return it
int	set_fd_out(int fd, char **outfile, int redir)
{
	int	i;
	int	size;

	i = -1;
	size = double_arr_len(outfile);
	while (outfile[++i])
	{
		if (redir < 3)
			fd = open(outfile[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			fd = open(outfile[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (i < size - 1)
			close(fd);
	}
	return (fd);
}

int	set_fd_in(int fd, char **infile)
{
	int	i;
	int	size;

	i = -1;
	size = double_arr_len(infile);
	while (infile[++i])
	{
		fd = open(infile[i], O_RDONLY);
		if (fd < 0)
		{
			perror(infile[i]);
			return (-1);
		}
		if (i < size - 1)
			close(fd);
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
int	*set_fd(char *line, int *fd, t_var *vars, t_env **env)
{
	char	**outfile;
	char	**infile;
	int		redirection;

	infile = get_infile(line);
	outfile = get_outfile(line);
	redirection = is_redirected(line);
	fd = find_files(fd, infile, outfile, redirection);
	if (fd[0] == -1)
	{
		vars->exit_statut = 1;
		update_exit_env(*env, vars);
	}
	return (free_db_array(infile), free_db_array(outfile), fd);
}

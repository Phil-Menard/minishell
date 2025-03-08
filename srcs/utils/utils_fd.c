#include "../minishell.h"

int	*init_fd(void)
{
	int	*fd;
	int	i;

	fd = malloc(3 * sizeof(int));
	i = -1;
	while (++i < 3)
		fd[i] = 1;
	return (fd);
}

//fd[0] : input | fd[1] : simple output | fd[2] : double output
int	*set_fd(char *line, int *fd)
{
	int		redirection;
	char	*infile;
	char	*outfile;

	infile = get_infile(line);
	outfile = get_outfile(line);
	redirection = is_redirected(line);
	if (redirection == 0)
	{
		fd[0] = open(infile, O_RDONLY);
		fd[1] = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	else if (redirection == 1)
		fd[0] = open(infile, O_RDONLY);
	else if (redirection == 2)
		fd[1] = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redirection == 3)
		fd[2] = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (redirection == 4)
	{
		fd[0] = open(infile, O_RDONLY);
		fd[2] = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	return (free(infile), free(outfile), fd);
}

void	close_multiple_fd(int *fd)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (fd[i] != 1 && fd[i] != -1)
			close(fd[i]);
		i++;
	}
}

//find which fd is opened for output
int	get_opened_fd_output(int *fd)
{
	if (fd[1] != 1)
		return (fd[1]);
	else if (fd[2] != 1)
		return (fd[2]);
	else
		return (1);
}

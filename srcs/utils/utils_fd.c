#include "../minishell.h"

int	*init_fd(void)
{
	int	*fd;
	int	i;

	fd = malloc(2 * sizeof(int));
	i = -1;
	while (++i < 2)
		fd[i] = 1;
	return (fd);
}

//fd[0] : input | fd[1] : output
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
		fd[1] = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (redirection == 4)
	{
		fd[0] = open(infile, O_RDONLY);
		fd[1] = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	return (free(infile), free(outfile), fd);
}

int	*init_and_set_fd(char *line)
{
	int	*fd;

	fd = init_fd();
	fd = set_fd(line, fd);
	return (fd);
}

void	close_multiple_fd(int *fd)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		if (fd[i] != 1 && fd[i] != -1)
			close(fd[i]);
		i++;
	}
	free(fd);
}

int	set_previous_fd(int *fd, int previous_fd)
{
	if (fd[0] != 1)
		previous_fd = fd[0];
	return (previous_fd);
}

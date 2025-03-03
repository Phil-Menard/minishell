#include "minishell.h"

//FD[0] : INPUT / FD[1] : SIMPLE OUTPUT / FD[2] : DOUBLE OUTPUT
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

//FIND WHICH FD IS OPENED FOR OUTPUT
int	get_opened_fd_output(int *fd)
{
	if (fd[1] != 1)
		return (fd[1]);
	else if (fd[2] != 1)
		return (fd[2]);
	else
		return (1);
}

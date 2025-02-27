#include "minishell.h"

void	redir_input(char *str, int *pipefd, char *path, char **arg)
{
	int		id;
	int		infile;
	char	*infile_name;

	infile_name = get_infile(str);
	infile = open(infile_name, O_RDONLY);
	if (infile == -1)
		perror(infile_name);
	id = fork();
	if (id == 0)
	{
		pipefd[0] = infile;
		close(pipefd[1]);
		if (dup2(pipefd[0], STDIN_FILENO) == -1)
			exit(EXIT_FAILURE);
		close(pipefd[0]);
		ft_execve(path, arg);
	}
	else
	{
		wait(NULL);
		close(infile);
		free(infile_name);
	}
}

void	redir_output(char *str, int *pipefd, char *path, char **arg)
{
	int		id;
	int		outfile;
	char	*outfile_name;

	outfile_name = get_outfile(str);
	printf("outfile : %s\n", outfile_name);
	outfile = open(outfile_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile == -1)
		perror(outfile_name);
	id = fork();
	pipefd[1] = outfile;
	if (id == 0)
	{
		close(pipefd[0]);
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			exit(EXIT_FAILURE);
		close(pipefd[1]);
		ft_execve(path, arg);
	}
	else
	{
		wait(NULL);
		close(outfile);
		free(outfile_name);
	}
}

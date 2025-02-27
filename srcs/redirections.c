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
	outfile = open(outfile_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile == -1)
		perror(outfile_name);
	id = fork();
	if (id == 0)
	{
		pipefd[1] = outfile;
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

void	pipe_me_that(int *pipefd, char *path, char **arg)
{
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
	close(pipefd[0]);
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	close(pipefd[1]);
	ft_execve(path, arg);
}

void	redir_in_and_out(char *str, int *pipefd, char *path, char **arg)
{
	int		id;
	int		infile;
	char	*infile_name;
	int		outfile;
	char	*outfile_name;

	infile_name = get_infile(str);
	infile = open(infile_name, O_RDONLY);
	if (infile == -1)
		perror(infile_name);
	outfile_name = get_outfile(str);
	outfile = open(outfile_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile == -1)
		perror(outfile_name);
	id = fork();
	pipefd[0] = infile;
	pipefd[1] = outfile;
	if (id == 0)
		pipe_me_that(pipefd, path, arg);
	else
	{
		wait(NULL);
		close(outfile);
		free(outfile_name);
	}
}

#include "minishell.h"

void	redir_input(char *str, char *path, char **arg)
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
		if (dup2(infile, STDIN_FILENO) == -1)
			exit(EXIT_FAILURE);
		ft_execve(path, arg);
	}
	else
	{
		wait(NULL);
		close(infile);
		free(infile_name);
	}
}

void	redir_output(char *str, char *path, char **arg)
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
		if (dup2(outfile, STDOUT_FILENO) == -1)
			exit(EXIT_FAILURE);
		ft_execve(path, arg);
	}
	else
	{
		wait(NULL);
		close(outfile);
		free(outfile_name);
	}
}

void	redir_output_append(char *str, char *path, char **arg)
{
	int		id;
	int		outfile;
	char	*outfile_name;

	outfile_name = get_outfile(str);
	outfile = open(outfile_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (outfile == -1)
		perror(outfile_name);
	id = fork();
	if (id == 0)
	{
		if (dup2(outfile, STDOUT_FILENO) == -1)
			exit(EXIT_FAILURE);
		ft_execve(path, arg);
	}
	else
	{
		wait(NULL);
		close(outfile);
		free(outfile_name);
	}
}

void	double_redir(char *path, char **arg, int infile, int outfile)
{
	
	if (dup2(infile, STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
	if (dup2(outfile, STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	ft_execve(path, arg);
}

void	redir_in_and_out(char *str, char *path, char **arg)
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
	if (find_occurences(str, '>') == 2)
		outfile = open(outfile_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		outfile = open(outfile_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile == -1)
		perror(outfile_name);
	id = fork();
	if (id == 0)
		double_redir(path, arg, infile, outfile);
	wait(NULL);
	close(outfile);
	free(outfile_name);
}

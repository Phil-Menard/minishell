#include "minishell.h"

//EXECVE WITH SIMPLE INPUT : <
void	redir_input(char *path, char **arg, int *fd)
{
	int	id;

	id = fork();
	if (id == 0)
	{
		if (dup2(fd[0], STDIN_FILENO) == -1)
			exit(EXIT_FAILURE);
		ft_execve(path, arg);
	}
	else
		wait(NULL);
}

//EXECVE WITH SIMPLE OUTPUT : >
void	redir_output(char *path, char **arg, int *fd)
{
	int	id;

	id = fork();
	if (id == 0)
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			exit(EXIT_FAILURE);
		ft_execve(path, arg);
	}
	else
		wait(NULL);
}

//EXECVE WITH DOUBLE OUTPUT : >>
void	redir_output_append(char *path, char **arg, int *fd)
{
	int	id;
	
	id = fork();
	if (id == 0)
	{
		if (dup2(fd[2], STDOUT_FILENO) == -1)
			exit(EXIT_FAILURE);
		ft_execve(path, arg);
	}
	else
		wait(NULL);
}

//EXECVE WITH INPUT AND SIMPLE OUTPUT : < / >
void	redir_in_and_simple_out(char *path, char **arg, int *fd)
{
	int	id;

	id = fork();
	if (id == 0)
	{
		if (dup2(fd[0], STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			exit(EXIT_FAILURE);
		ft_execve(path, arg);
	}
	else
		wait(NULL);
}

//EXECVE WITH INPUT AND DOUBLE OUTPUT : < / >>
void	redir_in_and_double_out(char *path, char **arg, int *fd)
{
	int	id;

	id = fork();
	if (id == 0)
	{
		if (fd[0] != 1)
		{
			if (dup2(fd[0], STDIN_FILENO) == -1)
				exit(EXIT_FAILURE);
		}
		if (fd[1] != 1)
		{
			if (dup2(fd[1], STDOUT_FILENO) == -1)
				exit(EXIT_FAILURE);
		}
		if (fd[2] != 1)
		{
			if (dup2(fd[2], STDOUT_FILENO) == -1)
				exit(EXIT_FAILURE);
		}
		ft_execve(path, arg);
	}
	else
		wait(NULL);
}

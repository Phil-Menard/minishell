#include "../minishell.h"

//execve with correct redirection
void	exec_redir(t_var *vars, int *fd, t_env **env, t_env **export)
{
	int	id;

	id = fork();
	if (id == 0)
	{
		if (dup2(fd[0], STDIN_FILENO) == -1)
		{
			perror("infile");
			exit(EXIT_FAILURE);
		}
		close(fd[0]);
		if (fd[1] != 1)
		{
			if (dup2(fd[1], STDOUT_FILENO) == -1)
			{
				perror("outfile");
				exit(EXIT_FAILURE);
			}
			close(fd[1]);
		}
		ft_execve(vars, env, export, fd);
	}
	else
		wait(NULL);
}

int	get_nb_redir_in(char **infiles)
{
	int	i;
	int	j;
	int	in;

	in = 0;
	i = 0;
	while (infiles[i])
	{
		j = 0;
		while (infiles[i][j])
		{
			if (infiles[i][j + 1])
				in++;
			j++;
		}
		i++;
	}
	return (in);
}

void	get_nb_redir(char **outfiles, int *out, int *out_append)
{
	int	i;
	int	j;

	i = 0;
	while (outfiles[i])
	{
		j = 0;
		while (outfiles[i][j])
		{
			if (outfiles[i][j + 1] 
				&& outfiles[i][j] == '>' && outfiles[i][j + 1] != '>')
			{
				i++;
				(*out)++;
				*out_append = 0;
			}
			if (outfiles[i][j + 1] 
				&& outfiles[i][j] == '>' && outfiles[i][j + 1] == '>')
			{
				i++;
				(*out_append)++;
				*out = 0;
			}
			j++;
		}
		i++;
	}
}

//check if there is a redirection
//0 = infile and outfile
//1 = infile only
//2 = outfile only
//3 = outfile in append mode only
//4 = infile and outfile in append mode
//-1 = no infile and no outfile
int	is_redirected(char **infiles, char **outfiles)
{
	int	in;
	int	out;
	int	out_append;

	out = 0;
	out_append = 0;
	in = get_nb_redir_in(infiles);
	get_nb_redir(outfiles, &out, &out_append);
	if (in > 0 && out > 0)
		return (0);
	else if (in > 0 && out_append > 0)
		return (4);
	else if (in > 0 && out == 0 && out_append == 0)
		return (1);
	else if (in == 0 && out > 0)
		return (2);
	else if (in == 0 && out_append > 0)
		return (3);
	else
		return (-1);
}

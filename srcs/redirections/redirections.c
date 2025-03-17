#include "../minishell.h"

//execve with correct redirection
void	exec_redir(char *path, char **arg, int *fd, t_env **env)
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
		ft_execve(path, arg, env);
	}
	else
		wait(NULL);
}

void	get_nb_redir(char *str, int *in, int *out, int *out_append)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i + 1] && str[i] == '<' && str[i + 1] != '<')
		{
			i++;
			(*in)++;
		}
		if (str[i + 1] && str[i] == '>' && str[i + 1] != '>')
		{
			i++;
			(*out)++;
			*out_append = 0;
		}
		if (str[i + 1] && str[i] == '>' && str[i + 1] == '>')
		{
			i++;
			(*out_append)++;
			*out = 0;
		}
		i++;
	}
}

//check if there is a redirection
int	is_redirected(char *str)
{
	int	in;
	int	out;
	int	out_append;

	in = 0;
	out = 0;
	out_append = 0;
	get_nb_redir(str, &in, &out, &out_append);
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

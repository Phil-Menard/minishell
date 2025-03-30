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

int	*init_and_set_fd(char *line, t_var *vars, t_env **env)
{
	int	*fd;

	fd = init_fd();
	fd = set_fd(line, fd, vars, env);
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

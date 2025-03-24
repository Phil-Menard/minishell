#include "../minishell.h"

void	ft_pwd(t_var *vars, int fd)
{
	char	*path;

	path = getcwd(NULL, 0);
	path = ft_straddchar(path, '\n');
	if (path)
	{
		ft_putstr_fd(path, fd);
		free(path);
		vars->exit_statut = 0;
	}
	else
	{
		perror("path error");
		vars->exit_statut = 1;
	}
}

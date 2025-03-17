#include "../minishell.h"

void	ft_pwd(int fd)
{
	char	*path;

	path = getcwd(NULL, 0);
	path = ft_straddchar(path, '\n');
	if (path)
	{
		ft_putstr_fd(path, fd);
		free(path);
	}
	else
		perror("path error");
}

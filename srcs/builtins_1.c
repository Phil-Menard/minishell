#include "minishell.h"

void	ft_pwd(int *fd)
{
	char	*path;
	int		fd_out;

	path = getcwd(NULL, 0);
	path = ft_straddchar(path, '\n');
	fd_out = get_opened_fd_output(fd);
	if (path)
	{
		ft_putstr_fd(path, fd_out);
		free(path);
	}
	else
		perror("path error");
}

void	ft_env(char **env, int *fd)
{
	char	*str;
	int		fd_out;
	int		i;

	fd_out = get_opened_fd_output(fd);
	i = 0;
	while (env[i])
	{
		str = ft_strdup(env[i]);
		str = ft_straddchar(str, '\n');
		ft_putstr_fd(str, fd_out);
		free(str);
		i++;
	}
}

void	ft_cd(char *str)
{
	char	*path;

	while (*str != ' ' && *str)
		str++;
	if (*str == '\0')
		path = getenv("HOME");
	else
	{
		str++;
		path = ft_strdup(str);
	}
	if (chdir(path) == -1)
		perror("chdir");
}

void	ft_exit(int *exit_code)
{
	printf("exit\n");
	*exit_code = 0;
}

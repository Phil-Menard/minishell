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

void	ft_cd(char *str, t_historic **historic)
{
	t_historic	*node;
	char		**arr;
	char		*path;
	int			i;

	arr = ft_split(str, " ");
	i = 1;
	if (arr[i] == NULL)
	{
		path = getenv("HOME");
	}
	else
		path = ft_strdup(arr[i]);
	if (arr[++i] != NULL)
		ft_putstr_fd("cd: too many arguments\n", 1);
	else if (chdir(path) == -1)
		perror("chdir");
	node = ft_new_cmd(str);
	ft_cmdadd_front(historic, node);
}

void	ft_exit(int *exit_code)
{
	ft_putstr_fd("exit\n", 1);
	*exit_code = 0;
}

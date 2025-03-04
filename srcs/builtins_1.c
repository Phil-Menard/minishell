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

void	ft_cd(char *str, t_hist **historic)
{
	t_hist	*node;
	char	**arr;
	char	*path;
	int		size;

	arr = ft_split(str, " ");
	size = 0;
	while (arr[size])
		size++;
	if (size > 2)
		ft_putstr_fd("cd: too many arguments\n", 1);
	else
	{
		if (arr[1] == NULL)
			path = getenv("HOME");
		else
			path = ft_strdup(arr[1]);
		if (chdir(path) == -1)
			perror("chdir");
		node = ft_new_cmd(str);
		ft_cmdadd_front(historic, node);
		if (arr[1])
			free(path);
	}
	free_db_array(arr);
}

void	ft_exit(int *exit_code)
{
	ft_putstr_fd("exit\n", 1);
	*exit_code = 0;
}

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

void	ft_env(t_env *env, int *fd)
{
	int		fd_out;

	fd_out = get_opened_fd_output(fd);
	print_env(env, fd_out);
}

void	ft_cd(char *str)
{
	char	**arr;
	char	*path;

	arr = ft_split(str, " ");
	if (double_arr_len(arr) > 2)
		ft_putstr_fd("cd: too many arguments\n", 1);
	else
	{
		if (arr[1] == NULL)
			path = getenv("HOME");
		else
			path = ft_strdup(arr[1]);
		
		if (chdir(path) == -1)
			perror("chdir");
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

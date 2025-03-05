#include "../minishell.h"

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

//get OLDPWD var from env and print it in good fd
char	*cd_oldpwd(t_env *env, int *fd)
{
	char	*str;
	char	*path;
	int		fd_out;

	fd_out = get_opened_fd_output(fd);
	path = get_var(env, "OLDPWD");
	str = ft_strjoin(path, "\n");
	ft_putstr_fd(str, fd_out);
	free(str);
	return (path);
}

void	ft_cd(char *str, t_env *env, int *fd)
{
	char	**arr;
	char	*path;
	char	*temp;

	arr = ft_split(str, " ");
	if (double_arr_len(arr) > 2 && fd[1] == 1 && fd[2] == 1)
		ft_putstr_fd("cd: too many arguments\n", 1);
	else
	{
		if (arr[1] == NULL || ft_strncmp(arr[1], "~", 1) == 0)
			path = getenv("HOME");
		else if (ft_strncmp(arr[1], "-", 1) == 0)
			path = cd_oldpwd(env, fd);
		else
			path = ft_strdup(arr[1]);
		temp = getcwd(NULL, 0);
		env = modify_env(env, "OLDPWD", temp);
		free(temp);
		if (chdir(path) == -1)
			perror("chdir");
		if (arr[1] && ft_strncmp(arr[1], "~", 1) != 0)
			free(path);
	}
	free_db_array(arr);
}

void	ft_exit(void)
{
	ft_putstr_fd("exit\n", 1);
	exit(EXIT_SUCCESS);
}

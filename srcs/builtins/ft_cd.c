#include "../minishell.h"

//get OLDPWD var from env and print it in good fd
char	*cd_oldpwd(t_env *env, int fd, int *x)
{
	char	*str;
	char	*path;

	path = NULL;
	path = ft_getenv(env, "OLDPWD");
	if (!path)
	{
		*x = 1;
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", fd);
		return (NULL);
	}
	str = ft_strjoin(path, "\n");
	ft_putstr_fd(str, fd);
	free(str);
	return (path);
}

void	set_oldpwd(t_env **env, int x)
{
	t_env	*node;
	char	*cwd;
	char	*oldpwd;
	char	*temp;

	if (x == 0)
	{
		cwd = NULL;
		oldpwd = NULL;
		cwd = getcwd(NULL, 0);
		oldpwd = ft_getenv(*env, "OLDPWD");
		if (!oldpwd)
		{
			temp = ft_strjoin("OLDPWD=", getenv("OLDPWD"));
			node = ft_new_env_node(temp);
			ft_env_add_back(env, node);
			free(temp);
		}
		else
			free(oldpwd);
		*env = modify_env(*env, "OLDPWD", cwd);
		free(cwd);
	}
}

//set path for chdir
char	*set_path_dir(char *arr, t_env **env, int fd)
{
	char	*path;
	int		x;

	path = NULL;
	x = 0;
	if (arr == NULL)
		path = ft_getenv(*env, "HOME");
	else if (ft_strncmp(arr, "-", 1) == 0)
	{
		if (ft_strlen(arr) == 1)
			path = cd_oldpwd(*env, fd, &x);
		else
		{
			x = 1;
			ft_putstr_fd("minishell: cd: ", fd);
			ft_putstr_fd(arr, fd);
			ft_putstr_fd(": invalid option\n", fd);
		}
	}
	else if (ft_strncmp(arr, "~", 1) == 0)
		path = getenv("HOME");
	else
		path = ft_strdup(arr);
	set_oldpwd(env, x);
	return (path);
}

void	ft_cd(char *str, t_env **env, int fd)
{
	char	**arr;
	char	*path;

	path = NULL;
	arr = ft_split(str, " ");
	if (double_arr_len(arr) > 2 && fd == 1)
		ft_putstr_fd("minishell: cd: too many arguments\n", 1);
	else
		path = set_path_dir(arr[1], env, fd);
	if (path)
	{
		if (chdir(path) == -1)
		{
			ft_putstr_fd("minishell: cd: ", fd);
			ft_putstr_fd(arr[1], fd);
			ft_putstr_fd(": No such file or directory\n", fd);
		}
		*env = modify_env(*env, "PWD", path);
		if (!arr[1] || (arr[1] && ft_strncmp(arr[1], "~", 1) != 0))
			free(path);
	}
	free_db_array(arr);
}

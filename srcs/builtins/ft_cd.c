#include "../minishell.h"

//get OLDPWD var from env and print it in good fd
char	*cd_oldpwd(t_env *env, int fd)
{
	char	*str;
	char	*path;

	path = get_var(env, "OLDPWD");
	str = ft_strjoin(path, "\n");
	ft_putstr_fd(str, fd);
	free(str);
	return (path);
}

void	ft_cd(char *str, t_env *env, int fd)
{
	char	**arr;
	char	*path;
	char	*temp;

	arr = ft_split(str, " ");
	if (double_arr_len(arr) > 2 && fd == 1)
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
		env = modify_env(env, "PWD", path);
		if (arr[1] && ft_strncmp(arr[1], "~", 1) != 0)
			free(path);
	}
	free_db_array(arr);
}

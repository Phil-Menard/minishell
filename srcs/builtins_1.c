#include "minishell.h"

void	ft_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path)
	{
		printf("%s\n", path);
		free(path);
	}
	else
		perror("path error");
}

void	ft_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
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

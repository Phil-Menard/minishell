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

void	handle_var(char *str, int *x)
{
	char	*var;
	char	*res;
	int		i;
	int		j;

	i = *x;
	j = 0;
	while (str[i] != '\0' && str[i] != ' ')
	{
		j++;
		i++;
	}
	var = ft_substr(str, *x, j);
	*x = i - 1;
	res = getenv(var);
	if (res)
		printf("%s", res);
	free(var);
}

void	ft_echo(char *str)
{
	int	i;
	int	option;

	option = 0;
	if (ft_strncmp(str, "echo -n", 7) == 0)
	{
		i = 7;
		option = 1;
	}
	else
		i = 5;
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			handle_var(str, &i);
		}
		else
			write(1, &str[i], 1);
		i++;
	}
	if (option == 0)
		printf("\n");
}

/*
// Name of the environment variable (e.g., PATH)
   const char *name = "PATH";
   // Get the value associated with the variable
   const char *env_p = getenv(name);
   if(env_p){
      printf("Your %s is %s\n", name, env_p);
   }
   return 0;
   */
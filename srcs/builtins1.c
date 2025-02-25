#include "minishell.h"

void	ft_pdw(void)
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

void	ft_echo(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{

		}
		else
		{
			write(1, &str[i], 1);
			i++;
		}
	}
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
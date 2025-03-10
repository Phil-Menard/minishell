#include "../minishell.h"

char	**lst_to_arr(t_env **env)
{
	t_env	*current;
	char	**arr;
	int		size;
	int		i;

	current = *env;
	size = env_size(*env);
	arr = malloc((size + 1) * sizeof(char *));
	i = 0;
	while (current)
	{
		arr[i] = ft_strdup(current->var);
		i++;
		current = current->next;
	}
	arr[i] = NULL;
	return (arr);
}

void	ft_execve(char *path, char **arg, t_env **env)
{
	char	**arr_env;

	arr_env = lst_to_arr(env);
	if (execve(path, arg, arr_env) == -1)
	{
		if (path)
			free(path);
		if (arg)
			free_db_array(arg);
		if (arr_env)
			free_db_array(arr_env);
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

#include "../minishell.h"

void	ft_unset(char *str, t_env **env)
{
	char	**arr;
	int		i;

	arr = ft_split(str, " ");
	i = 1;
	while (arr[i])
	{
		*env = remove_env_var(env, arr[i]);
		i++;
	}
	free_db_array(arr);
}


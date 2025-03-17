#include "../minishell.h"

void	ft_unset(char *str, t_env **env, t_env **export)
{
	char	**arr;
	int		i;

	arr = ft_split(str, " ");
	i = 1;
	while (arr[i])
	{
		*env = remove_env_var(env, arr[i], 0);
		*export = remove_env_var(export, arr[i], 11);
		i++;
	}
	free_db_array(arr);
}

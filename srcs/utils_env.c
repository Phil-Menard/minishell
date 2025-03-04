#include "minishell.h"

//find variable and update it
t_env	*modify_env(t_env *env, char *old_var, char *new_var)
{
	t_env	*current;
	char	**arr;

	current = env;
	while (current)
	{
		arr = ft_split(current->var, "=");
		if (ft_strncmp(arr[0], old_var, ft_strlen(arr[0])) == 0)
		{
			free(current->var);
			current->var = ft_join_mid(old_var, '=', new_var);
			free_db_array(arr);
			break ;
		}
		free_db_array(arr);
		current = current->next;
	}
	return (env);
}

char	*get_var(t_env *env, char *content)
{
	t_env	*current;
	char	**arr;
	char	*str;

	current = env;
	while (current)
	{
		arr = ft_split(current->var, "=");
		if (ft_strncmp(arr[0], content, ft_strlen(arr[0])) == 0)
		{
			str = ft_strdup(arr[1]);
			free_db_array(arr);
			return (str);
		}
		free_db_array(arr);
		current = current->next;
	}
	return (NULL);
}

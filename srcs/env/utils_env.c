#include "../minishell.h"

void	print_env(t_env *lst, int fd)
{
	while (lst != NULL)
	{
		ft_putstr_fd(lst->var, fd);
		ft_putchar_fd('\n', fd);
		lst = lst->next;
	}
}

//find variable and update it, arr[0] is variable name
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

void	free_env_node(char *var, t_env *node)
{
	free(var);
	free(node);
}

int	env_size(t_env *lst)
{
	int	size;

	size = 0;
	while (lst != NULL)
	{
		size += 1;
		lst = lst->next;
	}
	return (size);
}

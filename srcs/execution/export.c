#include "../minishell.h"

void	ft_export(t_env *export, int fd)
{
	print_env(export, fd);
}

//set export var from env but with declare -x at first and then between quotes
char	*set_export_var(char **arr, char *env_var)
{
	char	*str;
	int		i;

	i = 0;
	str = NULL;
	str = ft_straddstr(str, "declare -x ");
	str = ft_straddstr(str, arr[0]);
	while (env_var[i] != '=')
		i++;
	i++;
	str = ft_straddstr(str, "=\"");
	str = ft_straddstr(str, env_var + i);
	str = ft_straddchar(str, '\"');
	return (str);
}

t_env	*sort_export(t_env **lst)
{
	t_env	*current;
	char	*temp;
	int		size;

	current = *lst;
	while (current->next)
	{
		if (ft_strlen(current->var) >= ft_strlen(current->next->var))
			size = ft_strlen(current->var);
		else
			size = ft_strlen(current->next->var);
		if (ft_strncmp(current->var, current->next->var, size) > 0)
		{
			temp = ft_strdup(current->var);
			free(current->var);
			current->var = ft_strdup(current->next->var);
			free(current->next->var);
			current->next->var = ft_strdup(temp);
			free(temp);
			current = *lst;
		}
		else
			current = current->next;
	}
	return (*lst);
}

t_env	*init_export_lst(t_env **env, t_env **lst)
{
	t_env	*env_current;
	t_env	*lst_current;
	char	**arr;

	env_current = *env;
	lst_current = *lst;
	while (env_current)
	{
		arr = ft_split(env_current->var, "=");
		if (strncmp(arr[0], "_", 1) != 0)
		{
			lst_current = ft_new_env_node(set_export_var(arr, env_current->var));
			ft_env_add_back(lst, lst_current);
		}
		free_db_array(arr);
		env_current = env_current->next;
	}
	*lst = sort_export(lst);
	return (*lst);
}

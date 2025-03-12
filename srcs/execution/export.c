#include "../minishell.h"

//add var to export, x == 1 means there is a value to variable
t_env	*add_var_export(t_env **export, char *line, int x)
{
	t_env	*node;
	char	**arr;
	char	*str;
	char	*temp;
	int		i;

	arr = ft_split(line, "=");
	str = ft_strdup("declare -x ");
	str = ft_straddstr(str, arr[0]);
	if (x == 1)
	{
		str = ft_straddstr(str, "=\"");
		i = 1;
		while (line[i - 1] != '=')
			i++;
		temp = ft_substr(line, i, ft_strlen(line));
		str = ft_straddstr(str, temp);
		free(temp);
		str = ft_straddchar(str, '\"');
	}
	node = ft_new_env_node(ft_strdup(str));
	free(str);
	free_db_array(arr);
	ft_env_add_back(export, node);
	return (*export);
}

t_env	*add_var_env(t_env **env, char *line)
{
	t_env	*node;
	char	**arr;
	char	*str;
	char	*temp;
	int		i;

	arr = ft_split(line, "=");
	str = ft_strdup(arr[0]);
	str = ft_straddchar(str, '=');
	i = 1;
	while (line[i - 1] != '=')
		i++;
	temp = ft_substr(line, i, ft_strlen(line));
	str = ft_straddstr(str, temp);
	free(temp);
	node = ft_new_env_node(str);
	free(str);
	free_db_array(arr);
	ft_env_add_back(env, node);
	return (*env);
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

void	ft_export(char *line, t_env **env, t_env **export, int fd)
{
	char	**arr;
	int		i;

	i = 1;
	arr = ft_split(line, " ");
	if (!arr[i])
		print_env(*export, fd);
	else
	{
		while (arr[i])
		{
			if (find_occurences(arr[i], '=') == 0)
				*export = add_var_export(export, arr[i], 0);
			else
			{
				*export = add_var_export(export, arr[i], 1);
				*env = add_var_env(env, arr[i]);
			}
			i++;
		}
	}
	*export = sort_export(export);
	free_db_array(arr);
}

//set export var from env but with 'declare -x ' at first and then between quotes
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

t_env	*init_export_lst(t_env **env, t_env **lst)
{
	t_env	*env_current;
	t_env	*lst_current;
	char	**arr;
	char	*content;

	env_current = *env;
	lst_current = *lst;
	while (env_current)
	{
		arr = ft_split(env_current->var, "=");
		if (strncmp(arr[0], "_", 1) != 0)
		{
			content = set_export_var(arr, env_current->var);
			lst_current = ft_new_env_node(content);
			free(content);
			ft_env_add_back(lst, lst_current);
		}
		free_db_array(arr);
		env_current = env_current->next;
	}
	*lst = sort_export(lst);
	return (*lst);
}

#include "../minishell.h"

int	find_index_var(t_env **export, char *str)
{
	t_env	*current;
	int		index;
	int		size;

	index = 0;
	size = ft_strlen("declare -x ");
	current = *export;
	while (current)
	{
		if (ft_strncmp(current->var + size, str, ft_strlen(str)) == 0)
			return (index);
		index++;
		current = current->next;
	}
	return (0);
}

int	var_already_exist(t_env **export, char *str)
{
	t_env	*current;

	current = *export;
	while (current)
	{
		if (ft_strncmp(current->var, str, ft_strlen(str)) == 0)
			return (1);
		current = current->next;
	}
	return (0);
}

//check if variable name from export is valid
//0 is invalid
//1 is valid
//2 is valid and is '_' variable
int	check_valid_identifier(char *line)
{
	char	*str;
	int		size;
	int		i;

	str = ft_strdup(line);
	size = ft_strlen(str);
	free(str);
	if (size == 1 && line[0] == '_')
		return (2);
	i = 0;
	if (ft_isalpha(line[0]) == 0 && line[0] != '_')
		return (0);
	while (line[i])
	{
		if (ft_isalnum(line[i]) == 0 && line[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

//add var to export, without assigning it
t_env	*add_var_export(t_env **export, t_env **env, char *line, t_var *vars)
{
	t_env	*node;
	char	*str;

	if (check_valid_identifier(line) == 2)
		return (*export);
	if (check_valid_identifier(line) == 0)
	{
		ft_putstr_fd("minishell: export : '", 1);
		ft_putstr_fd(line, 1);
		ft_putstr_fd("': not a valid identifier\n", 1);
		vars->exit_statut = 1;
	}
	else
	{
		str = ft_strdup("declare -x ");
		str = ft_straddstr(str, line);
		if (var_already_exist(export, str) == 1)
			*export = remove_env_var(export, line, 11);
		if (var_already_exist(env, line) == 1)
			*env = remove_env_var(env, line, 0);
		node = ft_new_env_node(str);
		ft_env_add_back(export, node);
		free(str);
		vars->exit_statut = 0;
	}
	return (*export);
}

t_env	*assign_var_export(t_env **export, t_env **env, char *line, t_var *vars)
{
	t_env	*current;
	char	**arr;
	int		index;

	arr = ft_split(line, "=");
	*export = add_var_export(export, env, arr[0], vars);
	current = *export;
	index = find_index_var(export, arr[0]);
	while (index-- > 0)
		current = current->next;
	current->var = ft_straddstr(current->var, "=\"");
	index = 1;
	while (arr[index])
	{
		current->var = ft_straddstr(current->var, arr[index]);
		index++;
		if (arr[index])
			current->var = ft_straddchar(current->var, '=');
	}
	current->var = ft_straddchar(current->var, '\"');
	free_db_array(arr);
	return (*export);
}

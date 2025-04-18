#include "../minishell.h"

int	var_already_exist_bis(t_env **export, char *str)
{
	t_env	*current;
	char	**arr;

	arr = NULL;
	current = *export;
	while (current)
	{
		if (ft_strncmp(current->var, str, ft_strlen(str)) == 0)
		{
			arr = ft_split(current->var, "\"");
			if (arr[1])
			{
				free_db_array(arr);
				return (2);
			}
			else
				return (1);
		}
		current = current->next;
	}
	return (0);
}

void	end_var_export(t_env **exp, t_env *node, char *str, t_var *vars)
{
	ft_env_add_back(exp, node);
	free(str);
	vars->exit_statut = 0;
}

//add var to export, without assigning it
t_env	*add_var_exportl(t_env **exp, t_env **env, char *line, t_var *vars)
{
	t_env	*node;
	char	*str;

	if (check_valid_identifier(line) == 2)
		return (*exp);
	if (check_valid_identifier(line) == 0)
	{
		print_multiple_strfd("minishell: export : '", line,
			"': not a valid identifier\n", 2);
		vars->exit_statut = 1;
	}
	else
	{
		str = ft_strdup("declare -x ");
		str = ft_straddstr(str, line);
		if (var_already_exist_bis(exp, str) == 2)
			return (free(str), *exp);
		if (var_already_exist_bis(exp, str) == 1)
			*exp = remove_env_var(exp, line, 11);
		if (var_already_exist_bis(env, line) == 1)
			*env = remove_env_var(env, line, 0);
		node = ft_new_env_node(str);
		end_var_export(exp, node, str, vars);
	}
	return (*exp);
}

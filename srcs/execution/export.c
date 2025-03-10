#include "../minishell.h"

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
		lst_current = ft_new_env_node(set_export_var(arr, env_current->var));
		ft_env_add_back(lst, lst_current);
		free_db_array(arr);
		env_current = env_current->next;
	}
	return (*lst);
}

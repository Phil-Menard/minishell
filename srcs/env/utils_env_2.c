#include "../minishell.h"

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

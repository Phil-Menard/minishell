/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:09:13 by lefoffan          #+#    #+#             */
/*   Updated: 2025/04/11 11:41:42 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

//find variable and update it, arr[0] is variable name
t_env	*modify_env(t_env *env, char *var_name, char *content)
{
	t_env	*current;
	char	**arr;

	current = env;
	while (current)
	{
		arr = ft_split(current->var, "=");
		if (ft_cmpstr(arr[0], var_name) == 0)
		{
			free(current->var);
			current->var = ft_join_mid(var_name, '=', content);
			free_db_array(arr);
			break ;
		}
		free_db_array(arr);
		current = current->next;
	}
	return (env);
}

//get the value of content (content = $VAR)
char	*ft_getenv(t_env *env, char *content)
{
	t_env	*current;
	char	**arr;
	char	*str;

	current = env;
	while (current)
	{
		arr = ft_split(current->var, "=");
		if (ft_cmpstr(arr[0], content) == 0)
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

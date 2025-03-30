#include "../minishell.h"

//create new node
t_env	*ft_new_env_node(char *content)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	if (content == NULL)
		node->var = NULL;
	else
		node->var = ft_strdup(content);
	node->next = NULL;
	return (node);
}

//add node at the end of list
void	ft_env_add_back(t_env **lst, t_env *new)
{
	t_env	*current;

	if (*lst == NULL)
		*lst = new;
	else
	{
		current = *lst;
		while (current->next)
			current = current->next;
		current->next = new;
	}
}

//fill list with env
t_env	*fill_env(t_env **lst, char **envp)
{
	t_env	*node;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "_", 1) == 0)
			node = ft_new_env_node("_=/usr/bin/env");
		else
			node = ft_new_env_node(envp[i]);
		ft_env_add_back(lst, node);
		i++;
	}
	node = ft_new_env_node("?=");
	ft_env_add_back(lst, node);
	return (node);
}

//remove a node from env list
t_env	*remove_env_var(t_env **lst, char *str, int x)
{
	t_env	*current;
	t_env	*previous;
	int		str_size;

	previous = *lst;
	current = previous->next;
	str_size = ft_strlen(str);
	if (ft_strncmp(previous->var + x, str, str_size) == 0)
	{
		free_env_node(previous->var, previous);
		*lst = current;
		return (*lst);
	}
	while (current)
	{
		if (ft_strncmp(current->var + x, str, str_size) == 0)
		{
			previous->next = current->next;
			free_env_node(current->var, current);
			return (*lst);
		}
		previous = current;
		current = current->next;
	}
	return (*lst);
}

void	free_env(t_env *lst)
{
	t_env	*temp;

	temp = lst;
	while (temp)
	{
		temp = lst->next;
		free_env_node(lst->var, lst);
		lst = temp;
	}
}

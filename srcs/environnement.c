#include "minishell.h"

//create new node
t_env	*ft_new_env_node(char *content)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->var = content;
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
		node = ft_new_env_node(envp[i]);
		ft_env_add_back(lst, node);
		i++;
	}
	return (node);
}

void	print_env(t_env *lst, int fd)
{
	while (lst != NULL)
	{
		ft_putstr_fd(lst->var, fd);
		ft_putchar_fd('\n', fd);
		lst = lst->next;
	}
}

void	free_env(t_env *lst)
{
	t_env	*temp;

	temp = lst;
	while (temp)
	{
		temp = lst->next;
		free(lst);
		lst = temp;
	}
}

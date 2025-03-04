#include "minishell.h"

t_hist	*ft_new_cmd(char *cmd)
{
	t_hist	*node;

	node = malloc(sizeof(t_hist));
	if (!node)
		return (NULL);
	node->last_cmd = cmd;
	node->last_dir = NULL;
	node->next = NULL;
	if (cmd != NULL && ft_strncmp(cmd, "cd", 2) == 0)
		node->last_dir = getcwd(NULL, 0);
	return (node);
}

void	ft_cmdadd_front(t_hist **lst, t_hist *new)
{
	new->next = *lst;
	*lst = new;
}

void	print_hist(t_hist *lst)
{
	printf("printing historic : \n");
	while (lst != NULL)
	{
		printf("last_cmd : %s\n", lst->last_cmd);
		printf("last_dir : %s\n", lst->last_dir);
		lst = lst->next;
	}
	printf("\n");
}

void	free_historic(t_hist *lst)
{
	t_hist	*temp;

	temp = lst;
	while (temp)
	{
		temp = lst->next;
		free(lst->last_cmd);
		free(lst->last_dir);
		free(lst);
		lst = temp;
	}
}

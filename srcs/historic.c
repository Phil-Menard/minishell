#include "minishell.h"

t_historic	*ft_new_cmd(char *cmd)
{
	t_historic	*node;
	char		*path;

	node = malloc(sizeof(t_historic));
	if (!node)
		return (NULL);
	node->last_cmd = cmd;
	node->last_dir = NULL;
	node->next = NULL;
	if (cmd != NULL && ft_strncmp(cmd, "cd", 2) == 0)
	{
		path = getcwd(NULL, 0);
		node->last_dir = path;
	}
	return (node);
}

void	ft_cmdadd_front(t_historic **lst, t_historic *new)
{
	new->next = *lst;
	*lst = new;
}

void	print_historic(t_historic *lst)
{
	printf("printing historic : \n");
	while (lst != NULL)
	{
		printf("last_cmd : %s\n", lst->last_cmd);
		printf("last_dir : %s\n", lst->last_dir);
		lst = lst->next;
	}
}

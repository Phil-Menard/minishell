#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct s_tree
{
	char			*cmd;
	struct s_tree	*left;
	struct s_tree	*right;
}					t_tree;

void	ft_free_list(t_tree *tree)
{
	if (!tree)
		return ;
	ft_free_list(tree->left);
	ft_free_list(tree->right);
	free(tree);
}

void	ft_print_list(t_tree *tree)
{
	if (!tree)
		return ;
	printf("%s", tree->cmd);
	ft_print_list(tree->left);
	ft_print_list(tree->right);
}

t_tree	*ft_new_node(char *cmd)
{
	t_tree	*node;

	node = malloc(sizeof(t_tree));
	if (!node)
		return (NULL);
	node->left = NULL;
	node->right = NULL;
	node->cmd = cmd;
	return (node);
}

void	ft_add_node_end(t_tree *tree, const char *way, char *cmd)
{
	t_tree	*cur;

	cur = tree;
	if (strcmp(way, "left") == 0)
	{
		while (cur->left != NULL)
			cur = cur->left;
		cur->left = ft_new_node(cmd);
	}
	else if (strcmp(way, "right") == 0)
	{
		while (cur->right != NULL)
			cur = cur->right;
		cur->right = ft_new_node(cmd);
	}
}

int	main(void)
{
	t_tree	*tree;

	tree = malloc(sizeof(t_tree));
	if (!tree)
		return (1);
	tree->left = NULL;
	tree->right = NULL;
	tree->cmd = "echo ";
	ft_add_node_end(tree, "left", "-e ");
	ft_add_node_end(tree, "left", "left \n");
	ft_add_node_end(tree, "right", "-e ");
	ft_add_node_end(tree, "right", "right ");
	ft_print_list(tree);
	ft_free_list(tree);
	return (0);
}

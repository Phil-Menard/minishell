# include "minishell.h"

//! For testing, a retirer a la fin
void ft_print_tree(t_tree *root, int space)
{
	int i;

	if (!root)
		return;

	// Augmenter l'indentation pour le niveau suivant
	space += 5;

	// Afficher d'abord le sous-arbre droit
	ft_print_tree(root->right, space);

	// Afficher le nœud courant avec indentation
	printf("\n");
	i = 0;
	while (i++ < space)
		printf(" ");
	printf("%s\n", root->cmd);

	// Afficher ensuite le sous-arbre gauche
	ft_print_tree(root->left, space);
}

// recursively free the tree
void	ft_free_list(t_tree *tree)
{
	if (!tree)
		return ;
	ft_free_list(tree->left);
	ft_free_list(tree->right);
	free(tree);
}

// create a node, set the next left and right branch to null
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

// add a node at the end of the branch
void	ft_add_node_end(t_tree *tree, const char *branch, char *cmd)
{
	t_tree	*cur;

	cur = tree;
	if (ft_strcmp(branch, "left") == 0)
	{
		while (cur->left != NULL)
			cur = cur->left;
		cur->left = ft_new_node(cmd);
	}
	else if (ft_strcmp(branch, "right") == 0)
	{
		while (cur->right != NULL)
			cur = cur->right;
		cur->right = ft_new_node(cmd);
	}
}

/*	Split each words of line (separate by space)
	Parse the split tab, if a word is an executable (check with access() == 0),
		create a branch
*/
void	ft_create_branch(char *line)
{
	char	**split;
	int		i_arg;
	t_tree	*tree;


	split = ft_split(line, ' ');
	i_arg = 0;
	while (split[i_arg])
	{
		if (access(split[i_arg], X_OK) == 0)

	}
}

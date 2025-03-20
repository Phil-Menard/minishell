#include "../minishell.h"

//! For testing, a retirer a la fin
void	print_ast(t_ast *root, int space)
{
	int i;

	if (!root)
		return;

	// Augmenter l'indentation pour le niveau suivant
	space += 5;

	// Afficher d'abord le sous-arbre droit
	print_ast(root->right, space);

	// Afficher le nœud courant avec indentation
	printf("\n");
	i = 0;
	while (i++ < space)
		printf(" ");
	printf("%s\n", root->token);

	// Afficher ensuite le sous-arbre gauche
	print_ast(root->left, space);
}

// recursively free the tree
void	free_list(t_ast *tree)
{
	if (!tree)
		return ;
	free_list(tree->left);
	free_list(tree->right);
	free(tree);
}

t_ast	*new_node(char *token, t_token token_type)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->left = NULL;
	node->right = NULL;
	node->token = token;
	node->token = token_type;
	return (node);
}

// add a node at the end of the branch
void	add_node_end(t_ast *tree, const char *branch, t_ast *node)
{
	t_ast	*cur;

	if (!tree)
	{
		tree = node;
		return ;
	}
	cur = tree;
	if (ft_strncmp(branch, "left", 4) == 0)
	{
		while (cur->left != NULL)
			cur = cur->left;
		cur->left = node;
	}
	else if (ft_strncmp(branch, "right", 5) == 0)
	{
		while (cur->right != NULL)
			cur = cur->right;
		cur->right = node;
	}
}

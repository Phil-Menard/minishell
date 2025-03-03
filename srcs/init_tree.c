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

t_tree	*ft_new_node(char *cmd, char *arg)
{
	t_tree	*node;

	node = malloc(sizeof(t_tree));
	if (!node)
		return (NULL);
	node->left = NULL;
	node->right = NULL;
	node->cmd = cmd;
	node->arg = arg;
	return (node);
}

// add a node at the end of the branch
void	ft_add_node_end(t_tree *tree, const char *branch, t_tree *node)
{
	t_tree	*cur;

	cur = tree;
	if (ft_strcmp(branch, "left") == 0)
	{
		while (cur->left != NULL)
			cur = cur->left;
		cur->left = node;
	}
	else if (ft_strcmp(branch, "right") == 0)
	{
		while (cur->right != NULL)
			cur = cur->right;
		cur->right = node;
	}
}

/*	recupere la ligne, split la ligne, creer un node,
*/
void	ft_create_branch(char *line)
{
	char	**split;
	int		count;

	split = ft_split(line, ' ');
	count = 0;
	while (split[count] != NULL)
		count++;
	if (count == 3)
		split[1] = ft_strjoin_middle(split[1], ' ', split[2]);
	
	ft_new_node(split[0], split[1]);
}

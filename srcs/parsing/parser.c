# include "../minishell.h"

//* func called by main, call all other
void	ft_parse(char *line, t_env *env)
{
	t_ast	*tree;
	char	**tokens;

	if (!line)
		return ;
	tokens = ft_tokenizer(line); // lexing
	// create tree
	// exec
	ft_free_list(tree);
}




//* Join les bouts de split pour reconstituer la ligne de commande qui sera lance avec execve ou nos builtins
char	*ft_get_cmd(char **split, int *start)
{
	char	*str;

	if (ft_get_token(split[*start]) == CMD)
	{
		while (ft_get_token(split[*start]) == CMD)
		{
			str = ft_straddstr(str, split[*start]);
			if (split[*start + 1])
				str = ft_straddchar(str, ' ');
			(*start)++;
		}

	}
	return (str);
}




//* Create the AST recursively
void	ft_create_tree(t_ast *tree, char **split, int i_arg)
{
	if (ft_get_token(split[i_arg]) == CMD)
	{
		tree = ft_new_node(ft_get_cmd(split[i_arg], &i_arg), CMD);
		//ft_create_tree(tree);
	}
	// else if ()


	free_db_array(split);
	split = NULL;
}

// Fait un split, parcour le split ->creer un node, met dedans (fct qui join tout les bouts de split) jusqu'a croise un ||, | ou \0
// si on a croise un de ces signes, on fait un nouveau node a droite.
// Si on croise un ou &&, on fait un node enfant a gauche.

// node cmd, rien de particulier
// node &&, ||, | -> creer 2 enfant, 1 a gauche, 1 a droite
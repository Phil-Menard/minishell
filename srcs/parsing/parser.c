# include "minishell.h"

// Return a dup of tab, from tab[start] to tab[end], but start (from the call fct) is modified.
char	**ft_duptab(char **tab, int *start, int end)
{
	char	**dup;

	if (end < *start)
		return (NULL);
	dup = malloc(sizeof(char *) * (*start - end));
	if (!dup)
		return (NULL);
	while (*start <= end && dup[*start])
	{
		dup[*start] = ft_strdup(tab[*start]);
		start++;
	}
	dup[*start] = NULL;
	return (dup);
} //! a test

// Return the command cleaned of delset, parts delete from deslset are link by linker
char	*ft_clean_cmd(char *line, char *delset, char linker)
{
	char	**split;
	char	*str;
	int		count;

	split = ft_split(line, delset);
	count = 0;
	str = NULL;
	while (split[count])
	{
		str = ft_straddstr(str, split[count]);
		if (split[count + 1])
			str = ft_straddchar(str, linker);
		count++;
	}
	free_db_array(split);
	return (str);
}

void	ft_parse(char *line, t_env *env, int *exit_code)
{
	t_tree	*tree;
	char	*str;

	str = ft_clean_str(line);
	//* fct 
	// tree = ft_new_node(str);
	// printf("tree->cmd : %s\n", tree->cmd);
	builtins(tree->cmd, env, exit_code);
	free(str);
	ft_free_list(tree);
}

// Fait un split, parcour le split ->creer un node, met dedans (fct qui join tout les bouts de split) jusqu'a croise un ||, | ou \0
// si on a croise un de ces signes, on fait un nouveau node a droite.
// Si on croise un ou &&, on fait un node enfant a gauche.

// node cmd, rien de particulier
// node &&, ||, | -> creer 2 enfant, 1 a gauche, 1 a droite

t_token	ft_get_token(char *str)
{
	if (ft_strncmp(str, "&&", 2) == 0)
		return (AND);
	else if (ft_strncmp(str, "||", 2) == 0)
		return (OR);
	else if (ft_strncmp(str, "|", 1) == 0)
		return (PIPE);
	else
		return (CMD);
}

// Join les bouts de split pour reconstituer la ligne de commande qui sera lance avec execve ou nos builtins
char	*ft_get_cmd(char **split, int *start)
{
	char	*str;
	int		end;

	while (ft_get_token(split[*start]) == CMD)
	{
		/*str = ft_straddstr(str, split[*start]);
		if (split[*start + 1])
			str = ft_straddchar(str, ' ');
		(*start)++; */

	}
	return (str);
}

void	ft_create_tree(t_tree *tree, char **split, int i_arg)
{

	//TODO: creer le recursif pour les cmd, |, ||, ..
	if (ft_get_token(split[i_arg]) == CMD)
	{
		tree = ft_new_node(ft_get_cmd(split[i_arg], &i_arg), CMD);
		ft_create_tree(tree);// 
	}
}

# include "../minishell.h"

/**
 * 			- no need to handle special char with \
 */

void	parsing(char *line, t_env *env, t_var *vars)
{
	t_ast			*tree;
	t_token_builder	*tokens;

	if (!line)
		return ;
	if (!check_pair(line, '\'') || !check_pair(line, '\"'))
		quit("Unclosed quotes\n", 2, vars);
	tokens = tokenizer(line); // lexing
	// create tree
	// exec
	free_list(tree);
}

void	create_tree(t_ast *tree, char **split, int i_arg)
{

}

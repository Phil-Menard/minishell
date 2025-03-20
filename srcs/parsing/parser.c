# include "../minishell.h"

/**
 * 			- no need to handle special char with \ and odd nb of quotes
 * todo:	- handle var in " "
 */

void	parsing(char *line, t_env *env)
{
	t_ast			*tree;
	t_token_builder	*tokens;

	if (!line)
		return ;
	if (!check_pair(line, '\'') || !check_pair(line, '\"'))
	{
		printf("Error odd nb of quotes.\n");
		return ;
	}
	tokens = tokenizer(line); // lexing
	// create tree
	// exec
	free_list(tree);
}

void	create_tree(t_ast *tree, char **split, int i_arg)
{

}

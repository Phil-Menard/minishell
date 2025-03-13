# include "../minishell.h"

void	ft_parse(char *line, t_env *env)
{
	t_ast			*tree;
	t_token_builder	*tokens;

	if (!line)
		return ;
	if (!ft_check_pair(line, '\'') || !ft_check_pair(line, '\"'))
	{
		printf("Error odd nb of quotes.\n");
		return ;
	}
	tokens = ft_tokenizer(line); // lexing
	// create tree
	// exec
	ft_free_list(tree);
}

void	ft_create_tree(t_ast *tree, char **split, int i_arg)
{

}

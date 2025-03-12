# include "../minishell.h"

//* func called by main, call all other
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
	tokens = ft_tokenizer(ft_prep_tok(line)); // lexing
	// create tree
	// exec
	ft_free_list(tree);
}




//* Join les bouts de split pour reconstituer la ligne de commande qui sera lance avec execve ou nos builtins
// char	*ft_get_cmd(char **split, int *start)
// {
// 	char	*str;

// 	if (ft_get_token(split[*start]) == CMD)
// 	{
// 		while (ft_get_token(split[*start]) == CMD)
// 		{
// 			str = ft_straddstr(str, split[*start]);
// 			if (split[*start + 1])
// 				str = ft_straddchar(str, ' ');
// 			(*start)++;
// 		}

// 	}
// 	return (str);
// }
//* update : peut etre inutile au finale... 




//* Create the AST recursively
void	ft_create_tree(t_ast *tree, char **split, int i_arg)
{

	free_db_array(split);
	split = NULL;
}

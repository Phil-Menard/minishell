# include "../minishell.h"

/**
 * 			- no need to handle special char with \
 */

static char	*list_to_string(t_token_builder *tokens)
{
	char			*res;
	t_token_builder	*tmp;

	res = NULL;
	while (tokens && tokens->buf)
	{
		res = ft_straddstr(res, tokens->buf);
		res = ft_straddchar(res, ' ');
		tmp = tokens;
		tokens = tokens->next;
		free(tmp->buf);
		tmp->buf = NULL;
		free(tmp);
		tmp = NULL;
	}
	if (tokens && tokens->buf == NULL)
	{
		free(tokens->buf);
		free(tokens);
		tokens = NULL;
	}
	return (res);
}

void	parsing(t_env **env, t_var *vars, t_env **export)
{
	// t_ast			*tree;
	t_token_builder	*tokens;

	if (!vars->line)
		return ;
	if (!check_pair(vars->line, '\'') || !check_pair(vars->line, '\"'))
		quit("Unclosed quotes\n", 2, vars);
	tokens = tokenizer(vars->line, *env); // lexing
	free(vars->line);
	vars->line = list_to_string(tokens);
	if (vars->line)
		check_pipes(vars, env, export);
	// create tree
	// exec
	// free_list(tree);
}

/* static void	create_tree(t_ast *tree, char **split, int i_arg)
{

} */

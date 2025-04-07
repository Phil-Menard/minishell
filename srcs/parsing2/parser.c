#include "../minishell.h"

// If a token is expandable, expand it
// cad, if there is a $var -> replace by content in env
// otherwise if it's expandable but there's no $var, just let it.
static void	expander(t_token **tokens, t_env *env)
{
	t_token	*tmp;

	tmp = *tokens;
	while (tmp)
	{
		if (tmp->expandable)
			tmp->content = expand_str(tmp->content, env);
		tmp = tmp->next;
	}
}

// Change tokens after tokens of types redir to tokens of type redir_file,
// make it easier to add them to vars->cmd_line[].infile/outfile
static void	adjust_tokens_type(t_token **tokens)
{
	t_token	*tmp;

	tmp = *tokens;
	while (tmp)
	{
		if ((tmp->type == TOKEN_INFILE || tmp->type == TOKEN_OUTFILE)
			&& tmp->next && tmp->next->type == TOKEN_WORD)
			tmp->next->type = TOKEN_REDIR_FILE;
		tmp = tmp->next;
	}
}

static int	check_redir_file(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == TOKEN_INFILE || tokens->type == TOKEN_OUTFILE)
		{
			if (!tokens->next || (tokens->next && tokens->next->type != TOKEN_REDIR_FILE))
				return (ft_putstr_fd("syntax error near unexpected token\n", 1), 0);
		}
		tokens = tokens->next;
	}
	return (1);
}

void	parser(t_env **env, t_var *vars, t_env **export)
{
	t_token	*tokens;
	// t_leaf	*leafs;

	//if redir go to nowhere, go back to main (see Trello)
	tokens = tokenizer(vars->line);
	adjust_tokens_type(&tokens);
	expander(&tokens, *env);
	vars->tokens = tokens;
	if (check_redir_file(tokens) == 0)
		return ;
	// func to now nb of leafs (compared to &&, ||, ())
	// leafs = malloc(sizeof(t_leaf)); // for now only
	// if (!leafs)
		// return ;
	// leafs->cmd_line = set_cmd_line(tokens);
	vars->cmd_line = set_cmd_line(tokens, vars);
	check_pipes(vars, env, export);
}

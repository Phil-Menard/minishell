#include "../minishell.h"

void	free_tokens(t_token **tokens)
{
	t_token	*tmp;

	while (*tokens)
	{
		tmp = (*tokens)->next;
		if ((*tokens)->content)
		{
			free((*tokens)->content);
			(*tokens)->content = NULL;
		}
		free(*tokens);
		*tokens = tmp;
	}
}

size_t	count_tokens_type(t_token *tokens, t_token_type type)
{
	size_t	count;

	count = 0;
	while (tokens)
	{
		if (tokens->type == type)
			count++;
		tokens = tokens->next;
	}
	return (count);
}

size_t	count_in_tokens(t_token *tokens, char *to_find)
{
	size_t	count;

	count = 0;
	while (tokens)
	{
		if (ft_cmpstr(tokens->content, to_find) == 0)
			count++;
		tokens = tokens->next;
	}
	return (count);
}

static void	adjust_tokens_type(t_token **tokens)
{
	t_token	*tmp;

	tmp = *tokens;
	while (tmp)
	{
		if ((tmp->type == TOKEN_INFILE || tmp->type == TOKEN_OUTFILE) && tmp->next)
			tmp->next->type = TOKEN_REDIR_FILE;
		tmp = tmp->next;
	}
}

void	parser(t_env **env, t_var *vars, t_env **export)
{
	t_token	*tokens;
	// t_leaf	*leafs;

	//if redir go to nowhere, go back to main (see Trello)
	tokens = tokenizer(vars->line);
	adjust_tokens_type(&tokens);
	// func to now nb of leafs (compared to &&, ||, ())
	// leafs = malloc(sizeof(t_leaf)); // for now only
	// if (!leafs)
		// return ;
	// leafs->cmd_line = set_cmd_line(tokens);
	vars->cmd_line = set_cmd_line(tokens, vars);
	check_pipes(vars, env, export);
	free_tokens(&tokens);
}
#include "../minishell.h"

static size_t	count_words_tokens(t_token *tokens, size_t i)
{
	size_t	count;
	size_t	x;

	count = 0;
	x = 0;
	while (tokens)
	{
		if (tokens->type == TOKEN_PIPE)
		{
			if (x == i)
				return (count);
			x++;
		}
		if (x == i && tokens->type == TOKEN_WORD)
			count++;
		tokens = tokens->next;
	}
	return (count);
}

static char	**set_redir(t_token *tokens, size_t i, t_token_type type)
{
	size_t	j;
	size_t	x;
	char	**redir;

	redir = malloc(sizeof(char *) * (count_tokens_type(tokens, type) + 1));
	if (!redir)
		return (NULL);
	x = 0;
	j = 0;
	while (tokens)
	{
		if (x == i && tokens->type == type)
			redir[j++] = ft_straddstr(tokens->content, tokens->next->content);
		if (tokens->type == TOKEN_PIPE)
			x++;
		tokens = tokens->next;
	}
	redir[j] = NULL;
	return (redir);
}

static char	*set_cmd(t_token *tokens, size_t i)
{
	size_t	x;

	x = 0;
	while (tokens)
	{
		if (x == i && tokens->type == TOKEN_WORD)
			return (ft_strdup(tokens->content));
		if (tokens->type == TOKEN_PIPE)
			x++;
		tokens = tokens->next;
	}
	return (NULL);
}

static char	**set_args(t_token *tokens, size_t i)
{
	char	**args;
	size_t	x;
	size_t	i_arg;

	x = 0;
	i_arg = 0;
	args = malloc(sizeof(char *) * (count_words_tokens(tokens, i) + 1));
	while (tokens)
	{
		if (x == i && tokens->type == TOKEN_WORD)
			args[i_arg++] = ft_strdup(tokens->content);
		if (tokens->type == TOKEN_PIPE)
			x++;
		tokens = tokens->next;
	}
	args[i_arg] = NULL;
	return (args);
}

t_cmd_line	*set_cmd_line(t_token *tokens, t_var *vars)
{
	size_t	i;
	t_cmd_line	*cmd_line;

	vars->nb_cmd_line = count_in_tokens(tokens, "|") + 1;
	cmd_line = malloc(sizeof(t_cmd_line) * (vars->nb_cmd_line + 1));
	if (!cmd_line)
		return (NULL);
	i = 0;
	while (i < vars->nb_cmd_line)
	{
		cmd_line[i].cmd = set_cmd(tokens, i);
		cmd_line[i].args = set_args(tokens, i);
		cmd_line[i].infile = set_redir(tokens, i, TOKEN_INFILE);
		cmd_line[i].outfile = set_redir(tokens, i, TOKEN_OUTFILE);
		i++;
	}
	cmd_line[i].cmd = NULL;
	cmd_line[i].args = NULL;
	// cmd_line[i].infile = NULL;
	// cmd_line[i].outfile = NULL;
	return (cmd_line);
}
//ls | sort | rev
//i=0| i=1  | i=2
#include "../minishell.h"

static void	add_token(t_token **tokens, char *buffer, t_token_type type, t_mod mod)
{
	t_token	*new;
	int		expandable;

	if (mod == MOD_NORMAL || mod == MOD_DOUBLE)
		expandable = 1;
	else
		expandable = 0;
	new = new_token(buffer, type, NULL, expandable);
	if (!new)
		return ;
	if (*tokens == NULL)
		*tokens = new;
	else
		get_last_token(*tokens)->next = new;
}

static void	add_operator(t_token **tokens, char *line, int *i, t_mod mod)
{
	if (line[*i] == '>' && line[*i + 1] == '>')
	{
		add_token(tokens, ">>", TOKEN_OUTFILE, mod);
		(*i) += 1;
	}
	else if (line[*i] == '<' && line[*i + 1] == '<')
	{
		add_token(tokens, "<<", TOKEN_HEREDOC, mod);
		(*i) += 1;
	}
	else if (line[*i] == '|' && line[*i + 1] != '|')
		add_token(tokens, "|", TOKEN_PIPE, mod);
	else if (line[*i] == '<')
		add_token(tokens, "<", TOKEN_INFILE, mod);
	else if (line[*i] == '>')
		add_token(tokens, ">", TOKEN_OUTFILE, mod);
}

static inline void	add(t_token **tokens, char **buffer, t_mod mod)
{
	if (*buffer)
	{
		add_token(tokens, *buffer, TOKEN_WORD, mod);
		free(*buffer);
		*buffer = NULL;
	}
}

static void	quote_handler(char c, t_mod *mod, char **buffer)
{
	if (*mod == MOD_NORMAL && c == '\'')
		*mod = MOD_SINGLE;
	else if (*mod == MOD_NORMAL && c == '\"')
		*mod = MOD_DOUBLE;
	else if (*mod == MOD_SINGLE && c == '\'')
		*mod = MOD_NORMAL;
	else if (*mod == MOD_DOUBLE && c == '\"')
		*mod = MOD_NORMAL;
	else
		*buffer = ft_straddchar(*buffer, c);
}

t_token	*tokenizer(char *line)
{
	t_token	*tokens;
	int		i;
	t_mod	mod;
	char	*buffer;

	tokens = NULL;
	i = -1;
	mod = MOD_NORMAL;
	buffer = NULL;
	while (line[++i])
	{
		if ((line[i] == ' ' || (line[i] >= 9 && line[i] <= 13)) && mod == MOD_NORMAL)
			add(&tokens, &buffer, mod);
		else if ((line[i] == '<' || line[i] == '>' || line[i] == '|') && mod == MOD_NORMAL)
		{
			add(&tokens, &buffer, mod);
			add_operator(&tokens, line, &i, mod);
		}
		else if (line[i] == '\"' || line[i] == '\'')
			quote_handler(line[i], &mod, &buffer);
		else
			buffer = ft_straddchar(buffer, line[i]);
	}
	add(&tokens, &buffer, mod);
	return (tokens);
}

////////////////////////////////////////////////////////////////! 

/* int main(int ac, char **av)
{
	if (ac != 2)
		return (printf("nb arg\n"), 1);
	t_token	*tokens;
	
	tokens = tokenizer(av[1]);
	if (!tokens)
		return (printf("error\n"), 1);
	printlist(tokens);
	free_tokens(&tokens);
	return (0);
} */
#include "../minishell.h"

static void	add_token(t_token **tokens, char *buffer, t_token_type type, t_mod mod)
{
	t_token	*new_token;
	t_token	*tmp;
	
	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return ;
	new_token->content = ft_strdup(buffer);
	new_token->type = type;
	new_token->next = NULL;
	if (mod == MOD_NORMAL || mod == MOD_DOUBLE)
		new_token->expandable = 1;
	else
		new_token->expandable = 0;
	if (*tokens == NULL)
		*tokens = new_token;
	else
	{
		tmp = *tokens;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_token;
	}
}

static void	add_operator(t_token **tokens, char *line, int *i, t_mod mod)
{
	if (line[*i] == '>' && line[*i + 1] == '>')
	{
		add_token(tokens, ">>", TOKEN_OUTFILE, mod);
		(*i)++;
	}
	if (line[*i] == '<' && line[*i + 1] == '<')
	{
		add_token(tokens, "<<", TOKEN_INFILE, mod);
		(*i)++;
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
	// printf("quote\n");
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
		// printf("line[%d] : %c\n", i, line[i]);
		if ((line[i] == ' ' || (line[i] >= 9 && line[i] <= 13)) && mod == MOD_NORMAL)
		{
			// printf("space\n");
			add(&tokens, &buffer, mod);
		}
		else if ((line[i] == '<' || line[i] == '>' || line[i] == '|') && mod == MOD_NORMAL)
		{
			// printf("operator\n");
			add(&tokens, &buffer, mod);
			add_operator(&tokens, line, &i, mod);
		}
		else if (line[i] == '\"' || line[i] == '\'')
			quote_handler(line[i], &mod, &buffer);
		else
		{
			// printf("addchar\n");
			buffer = ft_straddchar(buffer, line[i]);
		}
	}
	// printlist(tokens);
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
#include "../minishell.h"

static void	add_token(t_token **tokens, char *buffer, t_token_type type)
{
	t_token	*new_token;
	t_token	*tmp;
	
	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return ;
	new_token->content = buffer;
	new_token->type = type;
	new_token->next = NULL;
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

static void	add_operator(t_token **tokens, char *line, int *i)
{
	if (line[*i] == '>' && line[*i + 1] == '>')
	{
		add_token(tokens, ft_strdup(">>"), TOKEN_OUTFILE);
		(*i)++;
	}
	if (line[*i] == '<' && line[*i + 1] == '<')
	{
		add_token(tokens, ft_strdup("<<"), TOKEN_INFILE);
		(*i)++;
	}
	else if (line[*i] == '|' && line[*i + 1] != '|')
		add_token(tokens, ft_strdup("|"), TOKEN_PIPE);
	else if (line[*i] == '<')
		add_token(tokens, ft_strdup("<"), TOKEN_INFILE);
	else if (line[*i] == '>')
		add_token(tokens, ft_strdup(">"), TOKEN_OUTFILE);
}

static inline void	add(t_token **tokens, char **buffer)
{
	t_token	*last;

// rajouter une verif 
	last = *tokens;
	while (last->next)
		last = last->next;
	if (*buffer)
	{
		if (last->type == TOKEN_INFILE)
			add_token(tokens, ft_strdup(*buffer), TOKEN_INFILE);
		else if (last->type == TOKEN_OUTFILE)
			add_token(tokens, ft_strdup(*buffer), TOKEN_OUTFILE);
		else
			add_token(tokens, ft_strdup(*buffer), TOKEN_WORD);
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
			add(&tokens, &buffer);
		}
		else if ((line[i] == '<' || line[i] == '>' || line[i] == '|') && mod == MOD_NORMAL)
		{
			// printf("operator\n");
			add(&tokens, &buffer);
			add_operator(&tokens, line, &i);
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
	add(&tokens, &buffer);
	return (tokens);
}

////////////////////////////////////////////////////////////////! 


/*static void	printlist(t_token *tokens)
{
	if (!tokens)
		printf("meeeeeeeeeeeeeerde\n");
	while (tokens)
	{
		printf("%s\n", tokens->content);
		tokens = tokens->next;
	}
}*/


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
#include "../minishell.h"

//* Split using a state machine
//		* for normal : split by whitespaces
//		* for quotes : take all btw quotes
// Verif if there's a pair nb of quotes ? Odd return error
// Use a strchr to find pos of quote, set a curs,
// duptab until curs, split the duptab put it in char **tokens.
// For quotes, strndup all btw (redo a strchr for quote 2) in the tab.

char	*ft_get_quotes(char *line, int start)
{
	int	curs;

	if (!line)
		return (NULL);
	if (line[start] == '\'')
		curs = ft_get_pos(line, start, '\'');
	else if (line[start] == '\"')
		curs = ft_get_pos(line, start, '\"');
	return (ft_strndup(line, start, curs));
}

void	ft_addchar_to_token(t_token_builder **builder, char c)
{
	t_token_builder	*last;

	if (!*builder)
	{
		*builder = malloc(sizeof(t_token_builder));
		if (!*builder)
			return (NULL);
		(*builder)->len = 1;
		(*builder)->buf[0] = c;
		(*builder)->next = NULL;
		return ;
	}
	last = *builder;
	while (last)
		last = last->next;
	if (last->len >= LEX_BUFF_SIZE)
	{
		last->next = malloc(sizeof(t_token_builder));
		if (!last->next)
			return ; // faire une fonction pour free toute la liste
		last = last->next;
		last->len = 0;
		last->next = NULL;
	}
	last->buf[last->len + 1] = c;
	
}

t_list	*ft_tokenizer(char *line)
{
	t_list	*tokens;
	int		i;

	if (!ft_check_pair(line, '\'') || !ft_check_pair(line, '\"'))
		return (NULL);

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			// add to list token_builder
		i++;
	}

	return (tokens);
}




//!-------------------------TESTS---------------------------------

int main()
{
	char *test = "echo 'hello world'";
	t_list *tokens = ft_tokenizer(test);

	while (tokens)
	{
		printf("Token: %s\n", ((t_ast *)tokens->content)->cmd);
		tokens = tokens->next;
	}
	return 0;
}

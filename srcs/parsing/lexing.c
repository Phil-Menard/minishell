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

	if (line[start] == '\'')
		curs = ft_get_pos(line, '\'');
	else if (line[start] == '\"')
		curs = ft_get_pos(line, '\"');
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

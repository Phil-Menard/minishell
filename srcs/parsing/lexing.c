#include "../minishell.h"

//* Split using a state machine
//		* for normal : split by whitespaces
//		* for quotes : take all btw quotes
// Verif if there's a pair nb of quotes ? Odd return error !
// Use a strchr to find pos of quote, set a curs,
// duptab until curs, split the duptab put it in char **tokens.
// For quotes, strndup all btw (redo a strchr for quote 2) in the tab.

//* Return pos of c in str, -1 if not founded.
int	ft_get_pos(char *str, char c)
{
	int	i;

	if (!str || !c)
		return (-1);
	i = 0;
	while (str[i] && str[i] != c)
		i++;
	if (str[i] == c)
		return (i);
	else
		return (-1);
}

//todo: checker for pair quotes
char	**ft_tokenizer(char *line)
{
	t_list	tokens;
	int		i;
	int		curs;
	t_state	cs; // current state

	i = -1;
	cs = NORMAL;
	// check pair quotes
	while (line[++i] != "\"")
	{

	}
}


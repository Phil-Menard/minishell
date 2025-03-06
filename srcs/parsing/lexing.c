#include "../minishell.h"

//* Split using a state machine
//		* for normal : split by whitespaces
//		* for quotes : take all btw quotes
// Verif if there's a pair nb of quotes ? Odd return error !
// Use a strchr to find pos of quote, set a curs,
// duptab until curs, split the duptab put it in char **tokens.
// For quotes, strndup all btw (redo a strchr for quote 2) in the tab.
char	**ft_tokenizer(char *line)
{
	char	**tokens;
	int		i;
	int		curs;
	t_state	cs; // current state

	i = -1;
	cs = NORMAL;
	while (line[++i])
	{

	}
}

//? Use char **tokens or a list that already contain nodes with their types, to skip detecting next step during tree creation ?
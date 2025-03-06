#include "../minishell.h"

//* Return a dup of tab, from tab[start] to tab[end], but start (from the call fct) is modified.
char	**ft_duptab(char **tab, int *start, int end)
{
	char	**dup;

	if (end < *start)
		return (NULL);
	dup = malloc(sizeof(char *) * (*start - end));
	if (!dup)
		return (NULL);
	while (*start <= end && dup[*start])
	{
		dup[*start] = ft_strdup(tab[*start]);
		start++;
	}
	dup[*start] = NULL;
	return (dup);
}

//* Detect the type of token str is.
//todo : add a detector for quotes
// 		(str of quotes must contains only a string delimited by quotes)
t_token	ft_get_token(char *str)
{
	if (ft_strncmp(str, "&&", 2) == 0)
		return (AND);
	else if (ft_strncmp(str, "||", 2) == 0)
		return (OR);
	else if (ft_strncmp(str, "|", 1) == 0)
		return (PIPE);
	else
		return (CMD);
}

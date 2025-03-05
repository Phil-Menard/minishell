#include "../minishell.h"

// Return a dup of tab, from tab[start] to tab[end], but start (from the call fct) is modified.
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

char	*ft_get_quotes(char *str)
{
	int	i;
	int	count;

	i = 0;
	while (str[i])
	{

	}
}

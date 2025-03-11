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

//* Return pos of c in str, -1 if not founded.
int	ft_get_pos(char *str, int start, char c)
{
	if (!str || !c)
		return (-1);
	while (str[start] && str[start] != c)
		start++;
	if (str[start] == c)
		return (start);
	else
		return (-1);
}

//* 1 = pair \ 0 = odd
int	ft_check_pair(char *line, char what)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == what)
			count++;
		i++;
	}
	if (count % 2 != 0)
		return (0);
	return (1);
}

t_token_builder	*ft_get_last(t_token_builder *node)
{
	t_token_builder	*last;

	last = node;
	while (last->next)
		last = last->next;
	return (last);
}

t_token_builder	*ft_new_tkb(size_t len, void *buf)
{
	t_token_builder	*new;

	new = ft_calloc(sizeof(t_token_builder), 1);
	if (!new)
		return (NULL);
	new->next = NULL;
	new->len = len;
	new->buf = buf;
	return (new);
}
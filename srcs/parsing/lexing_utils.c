#include "../minishell.h"

//* Detect the type of token str is.
t_token	get_token(char *str)
{
	if (ft_strncmp(str, "&&", 2) == 0)
		return (AND);
	else if (ft_strncmp(str, "||", 2) == 0)
		return (OR);
	else if (ft_strncmp(str, "|", 1) == 0)
		return (PIPE);
	else
		return (LEAF);
}

//* Return c index in str, 0 if not founded.
size_t	get_pos(char *str, size_t start, char c)
{
	if (!str || !c)
		return (0);
	while (str[start] && str[start] != c)
		start++;
	if (str[start] == c)
		return (start);
	return (0);
}

//* 1 = pair \ 0 = odd
int	check_pair(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'')
		{
			i++;
			while (line[i] && line[i] != '\'')
				i++;
			if (line[i] != '\'')
				return (0);
		}
		else if (line[i] == '\"')
		{
			i++;
			while (line[i] && line[i] != '\"')
				i++;
			if (line[i] != '\"')
				return (0);
		}
		i++;
	}
	return (1);
}

t_token_builder	*get_last(t_token_builder *node)
{
	t_token_builder	*last;

	if (!node)
		return (NULL);
	last = node;
	while (last->next)
		last = last->next;
	return (last);
}

t_token_builder	*new_tkb(size_t len, void *buf)
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

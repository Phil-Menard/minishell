#include "../minishell.h"

t_token	*new_token(char *content, t_token_type type, t_token *next, int expandable)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->content = ft_strdup(content);
	new->type = type;
	new->expandable = expandable;
	new->next = next;
	return (new);
}

t_token	*get_last_token(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

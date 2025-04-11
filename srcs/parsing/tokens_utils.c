#include "../minishell.h"

t_token	*new_token(char *str, t_token_type type, t_token *next, int exp)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->content = ft_strdup(str);
	new->type = type;
	new->expandable = exp;
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

void	crop_quotes(t_token **tokens)
{
	t_token	*tmp;
	char	*res;

	tmp = *tokens;
	while (tmp)
	{
		if (tmp->content[0] == '\''
			&& tmp->content[ft_strlen(tmp->content) - 1] == '\'')
		{
			res = ft_strtrim(tmp->content, "\'");
			free(tmp->content);
			tmp->content = res;
		}
		else if (tmp->content[0] == '\"'
			&& tmp->content[ft_strlen(tmp->content) - 1] == '\"')
		{
			res = ft_strtrim(tmp->content, "\"");
			free(tmp->content);
			tmp->content = res;
		}
		tmp = tmp->next;
	}
}

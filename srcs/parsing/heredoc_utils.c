#include "../minishell.h"

int	count_heredoc_cmdline(t_token *tokens, size_t i_pipe)
{
	int		count;
	size_t	i;
	t_token	*tmp;

	count = 0;
	i = 0;
	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == TOKEN_PIPE)
		{
			if (i == i_pipe)
				break ;
			else
				i++;
		}
		if (i == i_pipe && tmp->type == TOKEN_HEREDOC)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

char	**get_dels(t_token *tokens, size_t i_pipe, t_mod *mod)
{
	t_token	*tmp;
	char	**dels;
	size_t	i;
	size_t	x;

	tmp = tokens;
	dels = malloc(sizeof(char *) * (count_heredoc_cmdline(tokens, i_pipe) + 1));
	if (!dels)
		return (NULL);
	i = 0;
	x = 0;
	while (tmp)
	{
		if (i == i_pipe && tmp->type == TOKEN_HEREDOC)
		{
			dels[x++] = ft_strdup(tmp->next->content);
			if ((tmp->content[0] == '\'' && tmp->content[3] == '\'')
				|| (tmp->content[0] == '\"' && tmp->content[3] == '\"'))
				*mod = MOD_QUOTED;
		}
		else if (tmp->type == TOKEN_PIPE)
		{
			if (i == i_pipe)
				break ;
			else
				i++;
		}
		tmp = tmp->next;
	}
	return (dels[x] = NULL, dels);
}

#include "../minishell.h"

// count the nb of heredoc in the actual cmd_line (cmd between pipes)
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

// add to dels[x] the del (tmp->next->content)
// if del is quoted, mod = quoted so next the line will be expanded
static void	part_of_get_gels(char **dels, size_t *x, t_mod *mod, t_token *tmp)
{
	char	*res;
	t_token	*next;
	int		next_size;

	next = tmp->next;
	next_size = ft_strlen(next->content);
	if ((next->content[0] == '\'' && next->content[next_size - 1] == '\'')
		|| (next->content[0] == '\"' && next->content[next_size - 1] == '\"'))
		*mod = MOD_QUOTED;
	else
		*mod = MOD_NORMAL;
	dels[*x] = ft_strdup(tmp->next->content);
	if (dels[*x][0] == '"' && dels[*x][ft_strlen(dels[*x]) - 1] == '"')
	{
		res = ft_strtrim(dels[*x], "\"");
		free(dels[*x]);
		dels[*x] = res;
	}
	else if (dels[*x][0] == '\'' && dels[*x][ft_strlen(dels[*x]) - 1] == '\'')
	{
		res = ft_strtrim(dels[*x], "'");
		free(dels[*x]);
		dels[*x] = res;
	}
	(*x)++;
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
			part_of_get_gels(dels, &x, mod, tmp);
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

void	write_line_heredoc(char *line, int fd)
{
	char	*res;

	res = NULL;
	res = ft_straddstr(res, line);
	res = ft_straddchar(res, '\n');
	ft_putstr_fd(res, fd);
	free(res);
}

#include "../minishell.h"

char	**get_dels(t_token *tokens)
{
	t_token	*tmp;
	char	**dels;
	int		i;

	tmp = tokens;
	dels = malloc(sizeof(char *) * (count_tokens_type(tmp, TOKEN_HEREDOC) + 1));
	if (!dels)
		return (NULL);
	i = 0;
	while (tmp)
	{
		if (tmp->type == TOKEN_HEREDOC)
			dels[i++] = ft_strdup(tmp->next->content);
		tmp = tmp->next;
	}
	dels[i] = NULL;
	return (dels);
}

void	append_tmp_file(int fd, char *line)
{
	char	*res;

	res = NULL;
	res = ft_straddstr(res, line);
	res = ft_straddchar(res, '\n');
	ft_putstr_fd(res, fd);
	free(res);
}

void	add_heredoc_as_infile(t_token **tokens)
{
	t_token	*tmp;
	t_token	*redir;
	t_token	*redir_file;

	tmp = *tokens;
	while (tmp->next)
		tmp = tmp->next;
	redir = malloc(sizeof(t_token));
	if (!redir)
		return ;
	tmp->next = redir;
	redir->content = ft_strdup("<");
	redir->type = TOKEN_INFILE;
	redir->expandable = 0;
	redir_file = malloc(sizeof(t_token));
	if (!redir_file)
		return ;
	redir_file->content = ft_strdup(HEREDOC);
	redir_file->type = TOKEN_REDIR_FILE;
	redir_file->expandable = 0;
	redir_file->next = NULL;
	redir->next = redir_file;
}

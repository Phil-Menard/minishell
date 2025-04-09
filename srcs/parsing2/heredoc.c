#include "../minishell.h"

static int	count_heredoc_cmdline(t_token *tokens, size_t i_pipe)
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

static char	**get_dels(t_token *tokens, size_t i_pipe)
{
	t_token	*tmp;
	char	**dels;
	size_t	i;

	tmp = tokens;
	dels = malloc(sizeof(char *) * (count_heredoc_cmdline(tokens, i_pipe) + 1));
	if (!dels)
		return (NULL);
	i = 0;
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
			dels[i++] = ft_strdup(tmp->next->content);
		tmp = tmp->next;
	}
	dels[i] = NULL;
	return (dels);
}

static void	add_heredoc_as_infile(t_token **tokens, size_t i_pipe, char *file_name)
{
	t_token	*cmd_line_last_token;
	t_token	*infile;
	t_token	*infile_file;
	size_t	i;

	i = 0;
	cmd_line_last_token = *tokens;
	while (cmd_line_last_token->next->type != TOKEN_PIPE && i != i_pipe)
	{
		if (cmd_line_last_token->next->type == TOKEN_PIPE)
			i++;
		cmd_line_last_token = cmd_line_last_token->next;
	}
	infile_file = new_token(file_name, TOKEN_REDIR_FILE, cmd_line_last_token->next, 0);
	infile = new_token("<", TOKEN_INFILE, infile_file, 0);
	cmd_line_last_token->next = infile;
}

static void	append_line_to_file(char **dels, int fd)
{
	int		i;
	char	*line;
	char	*res;

	i = 0;
	while (i < double_arr_len(dels))
	{
		line = readline(">");
		if (ft_cmpstr(line, dels[i]) == 1 && i == (double_arr_len(dels) - 1))
		{
			res = NULL;
			res = ft_straddstr(res, line);
			res = ft_straddchar(res, '\n');
			ft_putstr_fd(res, fd);
			free(res);
		}
		if (ft_cmpstr(line, dels[i]) == 0)
			i++;
		free(line);
	}
}

void	ft_heredoc(t_token **tokens, t_var *vars)
{
	t_token	*tmp;
	char	**dels;
	char	*file_name;
	int		fd;
	size_t	i_pipe;

	// todo : expansion
	i_pipe = 0;
	while (i_pipe < vars->nb_cmd_line)
	{
		tmp = *tokens;
		file_name = ft_straddchar(HEREDOC, i_pipe + '0');
		fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			return ;
		dels = get_dels(tmp, i_pipe);//GERER MALLOC DELS
		append_line_to_file(dels, fd);
		close(fd);
		free_db_array(dels);
		free(file_name);
		add_heredoc_as_infile(tokens, i_pipe, file_name);
		i_pipe++;
	}
	tmp = *tokens;
	printlist(tmp);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:09:37 by lefoffan          #+#    #+#             */
/*   Updated: 2025/04/16 15:13:52 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// add before the pipe correspond to the cmd_line,
// the infile with the file created
static void	add_heredoc_infile(t_token **tokens, size_t i_pipe, char *file_name)
{
	t_token	*cmdl_last_tk;
	t_token	*infile;
	t_token	*infile_file;
	size_t	i;

	i = 0;
	cmdl_last_tk = *tokens;
	while (cmdl_last_tk->next->type != TOKEN_PIPE && i != i_pipe)
	{
		if (cmdl_last_tk->next->type == TOKEN_PIPE)
			i++;
		cmdl_last_tk = cmdl_last_tk->next;
	}
	infile_file = new_token(file_name, TOKEN_REDIR_FILE, cmdl_last_tk->next);
	infile = new_token("<", TOKEN_INFILE, infile_file);
	cmdl_last_tk->next = infile;
}

static char	*line_expand_or_not(char *line, t_env *env)
{
	char	*tmp;

	tmp = ft_strdup(line);
	line = expand_str(line, env);
	if (!line)
		line = tmp;
	else
		free(tmp);
	return (line);
}

static void	append_line_to_file(char **dels, int fd, t_mod *mod, t_env *env)
{
	int		i;
	char	*line;

	i = 0;
	while (i < double_arr_len(dels) && g_exit_signal != 2)
	{
		line = readline(">");
		if (line == NULL)
		{
			print_multiple_strfd
			("warning: here-document delimited by end-of-file (wanted (",
			dels[i], "))\n");
			break ;
		}
		if (ft_cmpstr(line, dels[i]) == 1 && i == (double_arr_len(dels) - 1))
		{
			if (*mod == MOD_NORMAL)
				line = line_expand_or_not(line, env);
			write_line_heredoc(line, fd);
		}
		if (ft_cmpstr(line, dels[i]) == 0)
			i++;
		free(line);
	}
}

static void	part_of_heredoc(char ***dels, int fd, t_mod *mod, t_env *env)
{
	append_line_to_file(*dels, fd, mod, env);
	close(fd);
	free_db_array(*dels);
}

void	ft_heredoc(t_token **tokens, t_var *vars, t_env *env)
{
	t_token	*tmp;
	char	**dels;
	int		fd;
	size_t	i_pipe;
	t_mod	mod;

	mod = MOD_NORMAL;
	i_pipe = 0;
	g_exit_signal = 7;
	rl_event_hook = rl_custom_hook;
	while (i_pipe < vars->nb_cmd_line && g_exit_signal != 2)
	{
		tmp = *tokens;
		vars->file_name = ft_straddchar(ft_strdup(HEREDOC), i_pipe + '0');
		fd = open(vars->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			return ;
		dels = get_dels(tmp, i_pipe, &mod);
		part_of_heredoc(&dels, fd, &mod, env);
		add_heredoc_infile(tokens, i_pipe, vars->file_name);
		free(vars->file_name);
		i_pipe++;
	}
}

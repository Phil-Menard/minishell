/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:09:40 by lefoffan          #+#    #+#             */
/*   Updated: 2025/04/18 15:11:41 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Change tokens types to redir_file after tokens of types redir
// (it check in the same time and print an error)
static int	specify_files_redir(t_token **tokens)
{
	t_token	*tmp;

	tmp = *tokens;
	while (tmp)
	{
		if (tmp->type == TOKEN_INFILE || tmp->type == TOKEN_OUTFILE
			|| tmp->type == TOKEN_HEREDOC)
		{
			if (tmp->next && tmp->next->type == TOKEN_WORD)
				tmp->next->type = TOKEN_REDIR_FILE;
			else
			{
				ft_putstr_fd("syntax error near unexpected token : ", 1);
				if (!tmp->next)
					printf("newline\n");
				else
					printf("%s\n", tmp->next->content);
				return (0);
			}
		}
		tmp = tmp->next;
	}
	return (1);
}

static void	remove_quotes(t_token **tokens)
{
	t_token	*tmp;
	char	quote;
	int		i;
	char	*res;

	tmp = *tokens;
	while (tmp)
	{
		res = NULL;
		i = -1;
		quote = 0;
		while (tmp->content && tmp->content[++i])
		{
			if (!quote && (tmp->content[i] == '"' || tmp->content[i] == '\''))
				quote = tmp->content[i];
			else if (quote && tmp->content[i] != quote)
				res = ft_straddchar(res, tmp->content[i]);
		}
		if (tmp->content && res)
		{
			free(tmp->content);
			tmp->content = ft_strdup(res);
			free(res);
		}
		tmp = tmp->next;
	}
}

void	parser(t_env **env, t_var *vars, t_env **export)
{
	t_token	*tokens;

	tokens = tokenizer(vars->line, *env);
	if (specify_files_redir(&tokens) == 0)
	{
		vars->tokens = tokens;
		vars->exit_statut = 2;
		update_exit_env(*env, vars);
		return ;
	}
	vars->nb_cmd_line = count_tokens_type(tokens, TOKEN_PIPE) + 1;
	if (count_tokens_type(tokens, TOKEN_HEREDOC) > 0)
		ft_heredoc(&tokens, vars, *env);
	remove_quotes(&tokens);
	vars->tokens = tokens;
	vars->cmd_line = set_cmd_line(tokens, vars);
	check_pipes(vars, env, export);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:09:40 by lefoffan          #+#    #+#             */
/*   Updated: 2025/04/11 11:46:06 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// If a token is expandable, expand it
// cad, if there is a $var -> replace by content in env
// otherwise if it's expandable but there's no $var, just let it.
void	expander(t_token **tokens, t_env *env)
{
	t_token	*tmp;

	tmp = *tokens;
	while (tmp)
	{
		if (tmp->expandable)
			tmp->content = expand_str(tmp->content, env);
		tmp = tmp->next;
	}
}

// Change tokens after tokens of types redir to tokens of type redir_file,
// make it easier to add them to vars->cmd_line[].infile/outfile
static void	specify_files_redir(t_token **tokens)
{
	t_token	*tmp;

	tmp = *tokens;
	while (tmp)
	{
		if ((tmp->type == TOKEN_INFILE || tmp->type == TOKEN_OUTFILE
				|| tmp->type == TOKEN_HEREDOC)
			&& tmp->next && tmp->next->type == TOKEN_WORD)
			tmp->next->type = TOKEN_REDIR_FILE;
		tmp = tmp->next;
	}
}

static int	check_redir_file(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == TOKEN_INFILE || tokens->type == TOKEN_OUTFILE
			|| tokens->type == TOKEN_HEREDOC)
		{
			if (!tokens->next
				|| (tokens->next && tokens->next->type != TOKEN_REDIR_FILE))
			{
				ft_putstr_fd("syntax error near unexpected token : ", 1);
				if (!tokens->next)
					printf("newline\n");
				else
					printf("%s\n", tokens->next->content);
				return (0);
			}
		}
		tokens = tokens->next;
	}
	return (1);
}

void	parser(t_env **env, t_var *vars, t_env **export)
{
	t_token	*tokens;

	tokens = tokenizer(vars->line);
	specify_files_redir(&tokens);
	if (check_redir_file(tokens) == 0)
	{
		vars->tokens = tokens;
		vars->exit_statut = 2;
		update_exit_env(*env, vars);
		return ;
	}
	vars->nb_cmd_line = count_tokens_type(tokens, TOKEN_PIPE) + 1;
	if (count_tokens_type(tokens, TOKEN_HEREDOC) > 0)
		ft_heredoc(&tokens, vars, *env);
	expander(&tokens, *env);
	crop_quotes(&tokens);
	vars->tokens = tokens;
	vars->cmd_line = set_cmd_line(tokens, vars);
	check_pipes(vars, env, export);
}

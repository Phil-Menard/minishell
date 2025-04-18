/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:09:49 by lefoffan          #+#    #+#             */
/*   Updated: 2025/04/18 18:32:21 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	add_token(t_tokenizer *t, char *op, t_token_type type)
{
	char	*tmp;

	if (op)
	{
		if (t->tokens == NULL)
			t->tokens = new_token(op, type, NULL);
		else
			last_token(t->tokens)->next = new_token(op, type, NULL);
	}
	else if (t->buf)
	{
		tmp = expand_str(t->buf, t->env);
		free(t->buf);
		t->buf = tmp;
		if (t->tokens == NULL)
			t->tokens = new_token(t->buf, type, NULL);
		else
			last_token(t->tokens)->next = new_token(t->buf, type, NULL);
		free(t->buf);
		t->buf = NULL;
	}
}

static void	add_operator(char *line, t_tokenizer *t)
{
	if (line[t->i] == '>' && line[t->i + 1] == '>')
	{
		add_token(t, ">>", TOKEN_OUTFILE);
		t->i += 1;
	}
	else if (line[t->i] == '<' && line[t->i + 1] == '<')
	{
		add_token(t, "<<", TOKEN_HEREDOC);
		t->i += 1;
	}
	else if (line[t->i] == '|' && line[t->i + 1] != '|')
		add_token(t, "|", TOKEN_PIPE);
	else if (line[t->i] == '<')
		add_token(t, "<", TOKEN_INFILE);
	else if (line[t->i] == '>')
		add_token(t, ">", TOKEN_OUTFILE);
}

static void	quote_handler(char c, t_tokenizer *t)
{
	if (t->mod == MOD_NORMAL && c == '\'')
		t->mod = MOD_SINGLE;
	else if (t->mod == MOD_NORMAL && c == '"')
		t->mod = MOD_DOUBLE;
	else if (t->mod == MOD_SINGLE && c == '\'')
		t->mod = MOD_NORMAL;
	else if (t->mod == MOD_DOUBLE && c == '"')
		t->mod = MOD_NORMAL;
	t->buf = ft_straddchar(t->buf, c);
}

t_token	*tokenizer(char *line, t_env *env)
{
	t_tokenizer	t;

	t.tokens = NULL;
	t.i = -1;
	t.mod = MOD_NORMAL;
	t.buf = NULL;
	t.env = env;
	while (line[++t.i])
	{
		if ((line[t.i] == ' ' || (line[t.i] >= 9 && line[t.i] <= 13))
			&& t.mod == MOD_NORMAL)
			add_token(&t, NULL, TOKEN_WORD);
		else if ((line[t.i] == '<' || line[t.i] == '>' || line[t.i] == '|')
			&& t.mod == MOD_NORMAL)
		{
			add_token(&t, NULL, TOKEN_WORD);
			add_operator(line, &t);
		}
		else if (line[t.i] == '\"' || line[t.i] == '\'')
			quote_handler(line[t.i], &t);
		else
			t.buf = ft_straddchar(t.buf, line[t.i]);
	}
	add_token(&t, NULL, TOKEN_WORD);
	return (t.tokens);
}

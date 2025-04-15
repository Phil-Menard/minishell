/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:09:49 by lefoffan          #+#    #+#             */
/*   Updated: 2025/04/15 19:53:32 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	add_token(t_tokenizer *t, char *buf, t_token_type type)
{
	t_expand	expand;
	char		*var;

	if (t->tokens && last_token(t->tokens)->type == TOKEN_HEREDOC
		&& t->mod == MOD_NORMAL)
		expand = EXPANDABLE;
	else if (t->mod == MOD_NORMAL || t->mod == MOD_DOUBLE)
	{
		expand = EXPANDED;
		var = expand_str(buf, t->env);
		if (var)
		{
			free(buf);
			buf = var;
		}
	}
	else
		expand = NOT_EXPANDABLE;
	if (t->tokens == NULL)
		t->tokens = new_token(buf, type, NULL, expand);
	else 
		last_token(t->tokens)->next = new_token(buf, type, NULL, expand);
	t->mod = MOD_NORMAL;
}

static void	add_operator(char *line, t_tokenizer *t)
{
	if (line[t->i] == '>' && line[t->i + 1] == '>')
	{
		add_token(t, ft_strdup(">>"), TOKEN_OUTFILE);
		t->i += 1;
	}
	else if (line[t->i] == '<' && line[t->i + 1] == '<')
	{
		add_token(t, ft_strdup("<<"), TOKEN_HEREDOC);
		t->i += 1;
	}
	else if (line[t->i] == '|' && line[t->i + 1] != '|')
		add_token(t, ft_strdup("|"), TOKEN_PIPE);
	else if (line[t->i] == '<')
		add_token(t, ft_strdup("<"), TOKEN_INFILE);
	else if (line[t->i] == '>')
		add_token(t, ft_strdup(">"), TOKEN_OUTFILE);
}

static void	add(t_tokenizer *t)
{
	if (t->buf)
	{
		add_token(t, t->buf, TOKEN_WORD);
		free(t->buf);
		t->buf = NULL;
	}
}

static void	quote_handler(char c, t_tokenizer *t)
{
	if (t->mod == MOD_NORMAL && c == '\'')
		t->mod = MOD_SINGLE;
	else if (t->mod == MOD_NORMAL && c == '"')
		t->mod = MOD_DOUBLE;
	else if (t->mod == MOD_SINGLE && c == '\'')
		add(t);
	else if (t->mod == MOD_DOUBLE && c == '"')
		add(t);
}

// l = line
// m = mod
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
			add(&t);
		else if ((line[t.i] == '<' || line[t.i] == '>' || line[t.i] == '|')
			&& t.mod == MOD_NORMAL)
		{
			add(&t);
			add_operator(line, &t);
		}
		else if (line[t.i] == '\"' || line[t.i] == '\'')
			quote_handler(line[t.i], &t);
		else
			t.buf = ft_straddchar(t.buf, line[t.i]);
	}
	add(&t);
	return (t.tokens);
}

////////////////////////////////////////////////////////////////! 

/* int main(int ac, char **av)
{
	if (ac != 2)
		return (printf("nb arg\n"), 1);
	t_token	*tokens;
	
	tokens = tokenizer(av[1]);
	if (!tokens)
		return (printf("error\n"), 1);
	printlist(tokens);
	free_tokens(&tokens);
	return (0);
} */
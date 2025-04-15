/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:09:49 by lefoffan          #+#    #+#             */
/*   Updated: 2025/04/15 16:23:13 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	add_token(t_token **tokens, char *buf, t_token_type type, t_mod *mod)
{
	t_token	*new;
	int		expandable;

	if (*tokens && last_token(*tokens)->type == TOKEN_HEREDOC
		&& *mod == MOD_NORMAL)
		expandable = 1;
	else if (*mod == MOD_NORMAL || *mod == MOD_DOUBLE)
		expandable = 1;
	else
		expandable = 0;
	new = new_token(buf, type, NULL, expandable);
	if (!new)
		return ;
	if (*tokens == NULL)
		*tokens = new;
	else
		last_token(*tokens)->next = new;
	*mod = MOD_NORMAL;
}

static void	add_operator(t_token **tokens, char *line, int *i, t_mod *mod)
{
	if (line[*i] == '>' && line[*i + 1] == '>')
	{
		add_token(tokens, ">>", TOKEN_OUTFILE, mod);
		(*i) += 1;
	}
	else if (line[*i] == '<' && line[*i + 1] == '<')
	{
		add_token(tokens, "<<", TOKEN_HEREDOC, mod);
		(*i) += 1;
	}
	else if (line[*i] == '|' && line[*i + 1] != '|')
		add_token(tokens, "|", TOKEN_PIPE, mod);
	else if (line[*i] == '<')
		add_token(tokens, "<", TOKEN_INFILE, mod);
	else if (line[*i] == '>')
		add_token(tokens, ">", TOKEN_OUTFILE, mod);
}

static void	add(t_token **tokens, char **buffer, t_mod *mod)
{
	if (*buffer)
	{
		add_token(tokens, *buffer, TOKEN_WORD, mod);
		free(*buffer);
		*buffer = NULL;
	}
}

static void	quote_handler(char c, t_mod *mod, char *buffer, t_token **tokens)
{
	if (*mod == MOD_NORMAL && c == '\'')
		*mod = MOD_SINGLE;
	else if (*mod == MOD_NORMAL && c == '"')
		*mod = MOD_DOUBLE;
	else if (*mod == MOD_SINGLE && c == '\'')
		add(tokens, buffer, mod);
	else if (*mod == MOD_DOUBLE && c == '"')
		add(tokens, buffer, mod);

}

// l = line
// m = mod
t_token	*tokenizer(char *l)
{
	t_token	*tokens;
	int		i;
	t_mod	m;
	char	*buffer;

	tokens = NULL;
	i = -1;
	m = MOD_NORMAL;
	buffer = NULL;
	while (l[++i])
	{
		if ((l[i] == ' ' || (l[i] >= 9 && l[i] <= 13)) && m == MOD_NORMAL)
			add(&tokens, &buffer, &m);
		else if ((l[i] == '<' || l[i] == '>' || l[i] == '|') && m == MOD_NORMAL)
		{
			add(&tokens, &buffer, &m);
			add_operator(&tokens, l, &i, &m);
		}
		else if (l[i] == '\"' || l[i] == '\'')
			quote_handler(l[i], &m, buffer, &tokens);
		else
			buffer = ft_straddchar(buffer, l[i]);
	}
	add(&tokens, &buffer, &m);
	return (tokens);
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
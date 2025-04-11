/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:09:34 by lefoffan          #+#    #+#             */
/*   Updated: 2025/04/11 12:26:42 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static char	*dels_quotes_handler(char *str, t_mod *mod)
{
	char	*res;
	int		i;

	res = NULL;
	i = 0;
	if (find_occurences(str, '\'') > 0
		|| find_occurences(str, '"') > 0)
	{
		*mod = MOD_QUOTED;
		while (str[i])
		{
			if (str[i] != '\'' && str[i] != '\"')
				res = ft_straddchar(res, str[i]);
			i++;
		}
		return (res);
	}
	else
		*mod = MOD_NORMAL;
	return (ft_strdup(str));
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
	dels[*x] = dels_quotes_handler(next->content, mod);
	if (dels[*x][0] == '"' || dels[*x][ft_strlen(dels[*x]) - 1] == '"')
	{
		res = ft_strtrim(dels[*x], "\"");
		free(dels[*x]);
		dels[*x] = res;
	}
	else if (dels[*x][0] == '\'' || dels[*x][ft_strlen(dels[*x]) - 1] == '\'')
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

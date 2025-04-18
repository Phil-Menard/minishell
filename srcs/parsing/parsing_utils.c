/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:09:56 by lefoffan          #+#    #+#             */
/*   Updated: 2025/04/18 18:34:41 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_var(char *content, int *i, t_env *env)
{
	char	*var;
	char	*str;

	var = NULL;
	(*i)++;
	while (content[*i] && (ft_isalnum(content[*i])
			|| content[*i] == '_' || content[*i] == '?'))
	{
		var = ft_straddchar(var, content[(*i)++]);
		if (content[*i - 1] == '?' && content[*i])
			break ;
	}
	str = ft_getenv(env, var);
	return (free(var), str);
}

// return content of the var in str (if there isn't just return the same)
char	*expand_str(char *str, t_env *env)
{
	char	*res;
	char	*var;
	int		i;

	res = NULL;
	i = 0;
	while (str[i])
	{
		if (is_protected(str[i]) != MOD_SINGLE && str[i] == '$' && str[i + 1]
			&& str[i + 1] != '"')
		{
			var = get_var(str, &i, env);
			res = ft_straddstr(res, var);
			free(var);
		}
		else
			res = ft_straddchar(res, str[i++]);
	}
	return (res);
}

void	free_tokens(t_token **tokens)
{
	t_token	*tmp;

	while (*tokens)
	{
		tmp = (*tokens)->next;
		if ((*tokens)->content != NULL)
		{
			free((*tokens)->content);
			(*tokens)->content = NULL;
		}
		free(*tokens);
		*tokens = tmp;
	}
}

// count tokens of a certain tokens->type
size_t	count_tokens_type(t_token *tokens, t_token_type type)
{
	size_t	count;

	count = 0;
	while (tokens)
	{
		if (tokens->type == type)
			count++;
		tokens = tokens->next;
	}
	return (count);
}

// count each patern char *to_find in the linked list *tokens
size_t	count_in_tokens(t_token *tokens, char *to_find)
{
	size_t	count;

	count = 0;
	while (tokens)
	{
		if (tokens->content && ft_cmpstr(tokens->content, to_find) == 0)
			count++;
		tokens = tokens->next;
	}
	return (count);
}

/* void	printlist(t_token *tokens)
{
	if (!tokens)
		printf("there's no list\n");
	printf("print list :\n");
	while (tokens)
	{
		printf("%s", tokens->content);
		if (tokens->next != NULL)
			printf(", ");
		tokens = tokens->next;
	}
	printf("\n");
} */
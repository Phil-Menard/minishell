#include "../minishell.h"

static inline void	part_of_expand(char **res, char **var, char **temp)
{
	*res = NULL;
	*var = NULL;
	*temp = NULL;
}

// Replace the string by it's expanded version
// free the string because planned to be use like
// str = expand_str(str, env);
// so str is replaced
char	*expand_str(char *content, t_env *env)
{
	char	*res;
	char	*var;
	char	*temp;
	int		i;

	part_of_expand(&res, &var, &temp);
	i = 0;
	while (content[i])
	{
		if (content[i] == '$')
		{
			i++;
			while ((content[i] && content[i] != ' ')
				|| (content[i] >= 9 && content[i] <= 13))
				var = ft_straddchar(var, content[i++]);
			temp = ft_getenv(env, var);
			res = ft_straddstr(res, temp);
			free(temp);
		}
		else
			res = ft_straddchar(res, content[i++]);
	}
	free(var);
	free(content);
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

void	printlist(t_token *tokens)
{
	if (!tokens)
		printf("there's no list\n");
	printf("print list :\n");
	while (tokens)
	{
		printf("%s", tokens->content);
		// if (tokens->type == TOKEN_PIPE)
		// 	printf(" (pipe)");
		// else if (tokens->type == TOKEN_WORD)
		// 	printf(" (word)");
		if (tokens->next != NULL)
			printf(", ");
		tokens = tokens->next;
	}
	printf("\n");
}

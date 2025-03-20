#include "../minishell.h"

// part of tokenizer
static void	space_handler(t_token_builder *tokens, char *line, int *i)
{
	while (line[*i] && line[*i] == ' ')
		(*i)++;
	if (tokens->buf != NULL)
		get_last(tokens)->next = new_tkb(0, NULL);
}

static char	*double_quotes(char *str, int start, int size)
{
	char	*res;

	res = ft_calloc(sizeof(char), size);
	if (!res)
		return (NULL);
	while (str[start] && start < size)
	{
		if (str[start] == '$')
		{
			
		}
		res = ft_straddchar(res, str[start]);
	}
}

//* Add all quoted text in buf into list token_builder.
//* Return size of quoted text.
static size_t	addquotes_to_token(t_token_builder **builder, char *line, int start)
{
	int				size;
	char			*quoted;
	t_token_builder	*last;

	if (!line)
		return (0);
	size = 0;
	if (line[start - 1] == '\'')
		size = get_pos(line, start, '\'') - start;
	else if (line[start - 1] == '\"')
		size = get_pos(line, start, '\"') - start;
	quoted = ft_strndup(line, start, size); // func for handle "$VAR"
	if (!quoted)
		return (0);
	last = get_last(*builder)->buf;
	if (!last)
		return (free(quoted), quoted = NULL, 0);
	last = ft_straddstr(last, quoted);
	return (free(quoted), size);
}

//* State machine
//		* Normal : add char by char to token, split on spaces
//		* Quotes : take all btw quotes and add it to token
t_token_builder	*tokenizer(char *line)
{
	t_token_builder	*tokens;
	int				i;
	int				quote_count;

	i = 0;
	quote_count = 0;
	tokens = new_tkb(0, NULL);
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			i++;
			if (++quote_count % 2 != 0)
				i += addquotes_to_token(&tokens, line, i);
		}
		else if (line[i] && line[i] == ' ')
			space_handler(tokens, line, &i);
		else if (line[i])
			get_last(tokens)->buf = ft_straddchar(get_last(tokens)->buf, line[i++]);
	}
	return (tokens);
}

//-------------------------TESTS---------------------------------

// To test lexing : cc -g -Wall -Wextra -Werror ../../libft/*.c ../utils/utils_2.c ../utils/utils.c lexing.c lexing_utils.c

/* int	main(void)
{
	char			*test = "            <Makefile \"grep echo \"e abc | \" |a";

	if (!check_pair(test, '\'') || !check_pair(test, '\"'))
	{
		printf("Error odd nb of quotes.\n");
		return 1;
	}
	t_token_builder	*tokens = tokenizer(test);
	t_token_builder	*tmp;

	printf("str : %s\n", test);
	while (tokens)
	{
		printf("Token: %s\n", tokens->buf);
		tmp = tokens;
		tokens = tokens->next;
		free(tmp->buf);
		tmp->buf = NULL;
		free(tmp);
		tmp = NULL;
	}
	return 0;
} */

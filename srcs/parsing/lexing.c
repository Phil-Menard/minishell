#include "../minishell.h"

// part of tokenizer
static void	space_handler(t_token_builder *tokens, char *line, int *i)
{
	while (line[*i] && line[*i] == ' ')
		(*i)++;
	if (tokens->buf != NULL)
		ft_get_last(tokens)->next = ft_new_tkb(0, NULL);
}

//* Add all quoted text in buf into list token_builder.
//* Return size of quoted text.
static size_t	ft_addquotes_to_token(t_token_builder **builder, char *line, int start)
{
	int		size;
	char	*quoted;

	if (!line)
		return (0);
	size = 0;
	if (line[start - 1] == '\'')
		size = ft_get_pos(line, start, '\'') - start;
	else if (line[start - 1] == '\"')
		size = ft_get_pos(line, start, '\"') - start;
	quoted = ft_strndup(line, start, size);
	ft_get_last(*builder)->buf = ft_straddstr(ft_get_last(*builder)->buf, quoted);
	return (free(quoted), size);
}

//* State machine
//		* Normal : add char by char to token, split on spaces
//		* Quotes : take all btw quotes and add it to token
t_token_builder	*ft_tokenizer(char *line)
{
	t_token_builder	*tokens;
	int				i;
	int				quote_count;

	i = 0;
	quote_count = 0;
	tokens = ft_new_tkb(0, NULL);
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			i++;
			if (++quote_count % 2 != 0)
				i += ft_addquotes_to_token(&tokens, line, i);
		}
		else if (line[i] && line[i] == ' ')
			space_handler(tokens, line, &i);
		else if (line[i])
			ft_get_last(tokens)->buf = ft_straddchar(ft_get_last(tokens)->buf, line[i++]);
	}
	return (tokens);
}

//-------------------------TESTS---------------------------------

// To test lexing : cc -g -Wall -Wextra -Werror ../../libft/*.c ../utils/utils_2.c ../utils/utils.c lexing.c lexing_utils.c

/* int	main(void)
{
	char			*test = "            <Makefile \"grep echo \"e abc | \" |a";

	if (!ft_check_pair(test, '\'') || !ft_check_pair(test, '\"'))
	{
		printf("Error odd nb of quotes.\n");
		return 1;
	}
	t_token_builder	*tokens = ft_tokenizer(test);
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

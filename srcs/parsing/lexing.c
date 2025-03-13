#include "../minishell.h"

//* Add all quoted text in buf into list token_builder.
//* Return size of quoted text.
static size_t	ft_addquotes_to_token(t_token_builder **builder, char *line, int start)
{
	int				size;
	t_token_builder	*last;
	char			*quoted;

	if (!line)
		return (0);
	size = 0;
	if (line[start - 1] == '\'')
		size = ft_get_pos(line, start, '\'') - start;
	else if (line[start - 1] == '\"')
		size = ft_get_pos(line, start, '\"') - start;
	quoted = ft_strndup(line, start, size);
	last = ft_get_last(*builder);
	last->buf = ft_straddstr(last->buf, quoted);
	return (ft_strlen(quoted));
}


//* State machine
//		* Normal : add char by char to token, split to spaces
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
		{
			while (line[i] && line[i] == ' ')
				i++;
			ft_get_last(tokens)->next = ft_new_tkb(0, NULL);
		}
		else if (line[i])
			ft_get_last(tokens)->buf = ft_straddchar(ft_get_last(tokens)->buf, line[i++]);
	}
	return (tokens);
}

//-------------------------TESTS---------------------------------

int	main(void)
{
	char			*test = "e\'ch\'o \"hello world\" peach \"!\"";
	t_token_builder	*tokens = ft_tokenizer(test);

	printf("str : %s\n", test);
	while (tokens)
	{
		printf("Token: %s\n", tokens->buf);
		tokens = tokens->next;
	}
	return 0;
}

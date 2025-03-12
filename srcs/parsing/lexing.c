#include "../minishell.h"

//* Add all quoted text in buf into list token_builder
void	ft_addquotes_to_token(t_token_builder **builder, char *line, int start)
{
	int				size;
	t_token_builder	*last;
	char			*quoted;

	if (!line)
		return ;
	size = 0;
	if (line[start++] == '\'')
		size = ft_get_pos(line, start, '\'');
	else if (line[start++] == '\"')
		size = ft_get_pos(line, start, '\"');
	printf("quoted len: %d\n", size);
	quoted = ft_strndup(line, start, size);
	printf("quoted: %s\n", quoted);
	last = ft_get_last(*builder);
	last->buf = ft_straddstr(last->buf, quoted);

}


//* State machine
//		* Normal : add char by char to a token
//		* Quotes : take all btw quotes and add it to a new token
/**
 * - si tu croises un espace en mode normal tu fait un nouveau node (et tu le skip)
 * - tu ajoutes tout au dernier node creer
 * 		- quotes ajoute tout au node
*/
t_token_builder	*ft_tokenizer(char *line)
{
	t_token_builder	*tokens;
	int				i;

	tokens = NULL;
	i = -1;
	tokens = ft_new_tkb(0, NULL);
	while (line[++i])
	{
		if (line[i] && (line[i] == '\'' || line[i] == '\"')
			&& (!ft_strfind(line + i, "\'") || !ft_strfind(line + i, "\"")))
		{
			ft_addquotes_to_token(&tokens, line, i);
			i += ft_strlen(ft_get_last(tokens)->buf) + 1;
		}
		else if (line[i] && line[i] == ' ')
		{
			while (line[i] && line[i] == ' ')
				i++;
			ft_get_last(tokens)->next = ft_new_tkb(0, NULL);
		}
		else if (line[i])
			ft_get_last(tokens)->buf = ft_straddchar(ft_get_last(tokens)->buf, line[i]);
		printf("last buf: %s\n", ft_get_last(tokens)->buf);
	}
	return (tokens);
}

//-------------------------TESTS---------------------------------

int	main(void)
{
	char			*test = "echo 'hello world' peach \"!\"";
	t_token_builder	*tokens = ft_tokenizer(test);

	printf("str : %s\n", test);
	while (tokens)
	{
		printf("Token: %s\n", tokens->buf);
		tokens = tokens->next;
	}
	return 0;
}

#include "../minishell.h"

//* Add all quoted text in buf into list token_builder
void	ft_addquotes_to_token(t_token_builder **builder, char *line, int start)
{
	int				size;
	t_token_builder	*last;

	if (!line)
		return ;
	if (line[start++] == '\'')
		size = ft_get_pos(line, start, '\'') - start;
	else if (line[start] == '\"')
		size = ft_get_pos(line, start, '\"') - start;
	last = ft_get_last(*builder);
	last->next = ft_new_tkb(size, ft_strndup(line, start, size));
}

//* Add char by char to buf into list token_builder
void	ft_addchar_to_token(t_token_builder **builder, char c)
{
	t_token_builder	*last;

	if (!*builder)
	{
		*builder = ft_new_tkb(1, ft_calloc(sizeof(char), LEX_BUFF_SIZE));
		(*builder)->buf[0] = c;
		return ;
	}
	last = ft_get_last(*builder);
	if (last->len >= LEX_BUFF_SIZE)
		last->next = ft_new_tkb(0, ft_calloc(sizeof(char), LEX_BUFF_SIZE));
	last->buf[last->len++] = c;
}

//* State machine
//		* Normal : add char by char to a token
//		* Quotes : take all btw quotes and add it to a new token
t_token_builder	*ft_tokenizer(char *line)
{
	t_token_builder	*tokens;
	int				i;

	tokens = NULL;
	i = -1;
	while (line[++i])
	{
		if (line[i] && (line[i] == '\'' || line[i] == '\"')
			&& (ft_strfind(line + i, "\'") || ft_strfind(line + i, "\"")))
		{
			ft_addquotes_to_token(&tokens, line, i);
			i += ft_strlen(ft_get_last(tokens)->buf) + 1;
			if (line[i + 1] != '\0')
				ft_get_last(tokens)->next = ft_new_tkb(0, ft_calloc(sizeof(char), LEX_BUFF_SIZE));
		}
		else
			ft_addchar_to_token(&tokens, line[i]);
	}
	return (tokens);
}

/** 
 * todo : plus qu'a concat les tokens comme il faut -> detecter le type du token (cmd, arg, pipe, and, or ?)
 * todo : les mettres dans des nodes
 * todo : s'occuper de la creation de l'ast pour mettre les nodes aux bons endroits
 * */

//-------------------------TESTS---------------------------------

// int	main(void)
// {
// 	char			*test = "echo 'hello world' peach \"!\"";
// 	t_token_builder	*tokens = ft_tokenizer(test);

// 	printf("str : %s\n", test);
// 	while (tokens)
// 	{
// 		printf("Token: %s\n", tokens->buf);
// 		tokens = tokens->next;
// 	}
// 	return 0;
// }

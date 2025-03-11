#include "../minishell.h"
void	ft_addchar_to_token(t_token_builder **builder, char c);

//* Add all quoted text in buf into list token_builder
void	ft_addquotes_to_token(t_token_builder **builder, char *line, int start)
{
	int				curs;
	t_token_builder	*last;

	if (!line)
		return ;

	if (line[start] == '\'')
		curs = ft_get_pos(line, ++start, '\'');
	else if (line[start] == '\"')
		curs = ft_get_pos(line, ++start, '\"');


	last = ft_get_last(*builder);
	last->next = ft_calloc(sizeof(t_token_builder), 1);
	if (!last)
		return ; // free all list
	last = last->next;

	last->buf = ft_strndup(line, start, curs - start);
	if (!last->buf)
		printf("strndup not work\n");
	last->len = ft_strlen(last->buf);
	last->next = NULL;
	printf("addquote : %s\n", last->buf);
}




//* Add char by char to buf into list token_builder
void	ft_addchar_to_token(t_token_builder **builder, char c)
{
	t_token_builder	*last;

	if (!*builder)
	{
		*builder = ft_calloc(sizeof(t_token_builder), 1);
		if (!*builder)
			return ;
		(*builder)->len = 1;
		(*builder)->buf = ft_calloc(sizeof(char), LEX_BUFF_SIZE);
		(*builder)->buf[0] = c;
		(*builder)->next = NULL;
		return ;
	}
	last = ft_get_last(*builder);
	if (last->len >= LEX_BUFF_SIZE)
	{
		last->next = ft_calloc(sizeof(t_token_builder), 1);
		if (!last->next)
			return ; // faire une fonction pour free toute la liste
		last = last->next;
		last->buf = ft_calloc(sizeof(char), LEX_BUFF_SIZE);
		last->len = 0;
		last->next = NULL;
	}
	last->buf[last->len++] = c;
	printf("addchar : %s\n", last->buf);
}






//* State machine
//		* Normal : add char by char to buf
//		* Quotes : take all btw quotes and add it to buf
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
			i += ft_strlen(ft_get_last(tokens)->buf);
		}
		else
			ft_addchar_to_token(&tokens, line[i]);
	}

	return (tokens);
}




//!-------------------------TESTS---------------------------------

int main()
{
	char *test = "echo 'hello world'";
	t_token_builder *tokens = ft_tokenizer(test);

	printf("str : %s\n", test);
	while (tokens)
	{
		printf("Token: %s\n", tokens->buf);
		tokens = tokens->next;
	}
	return 0;
}

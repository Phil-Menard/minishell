#include "../minishell.h"
void	ft_addchar_to_token(t_token_builder **builder, char c);

//* Add all quoted text in buf into list token_builder
void	ft_addquotes_to_token(t_token_builder **builder, char *line, int *start)
{
	int				curs;
	t_token_builder	*last;
	int				i;

	if (!line)
		return ;

	if (line[*start] == '\'')
		curs = ft_get_pos(line, (*start), '\'');
	else if (line[*start] == '\"')
		curs = ft_get_pos(line, (*start), '\"');


	last = *builder;
	while (last->next)
		last = last->next;
	last = ft_calloc(sizeof(t_token_builder), 1);
	if (!last)
		return ; // free

	last->buf = ft_calloc(sizeof(char), curs - *start);
	if (!last->buf)
		return ;
	last->buf = ft_strndup(line, *start, curs - *start);

	printf("Quoted : %s\n", last->buf);
}




//* Add char by char to buf into list token_builder
void	ft_addchar_to_token(t_token_builder **builder, char c)
{
	t_token_builder	*last;

	if (!*builder)
	{
		*builder = malloc(sizeof(t_token_builder));
		if (!*builder)
			return ;
		(*builder)->len = 1;
		(*builder)->buf = ft_calloc(sizeof(char), LEX_BUFF_SIZE);
		(*builder)->buf[0] = c;
		(*builder)->next = NULL;
		return ;
	}
	last = *builder;
	while (last->next)
		last = last->next;
	if (last->len >= LEX_BUFF_SIZE)
	{
		last = malloc(sizeof(t_token_builder));
		if (!last)
			return ; // faire une fonction pour free toute la liste
		last->len = 0;
		last->next = NULL;
		last->buf = ft_calloc(sizeof(char), LEX_BUFF_SIZE);
	}
	last->buf[last->len++] = c;
	printf("Buf : %s\n", last->buf);
}






//* State machine
//		* Normal : add char by char to buf
//		* Quotes : take all btw quotes and add it to buf
t_token_builder	*ft_tokenizer(char *line)
{
	t_token_builder	*tokens;
	int				i;

	if (!ft_check_pair(line, '\'') || !ft_check_pair(line, '\"'))
		return (printf("Error odd nb of quotes.\n"), NULL);

	tokens = NULL;
	i = 0;
	while (line[i])
	{
		if (line[i] && (line[i] == '\'' || line[i] == '\"')
			&& (ft_strfind(line + i, "\'") || ft_strfind(line + i, "\"")))
			ft_addquotes_to_token(&tokens, line, &i);
		else
			ft_addchar_to_token(&tokens, line[i]);
		i++;
	}

	return (tokens);
}




//!-------------------------TESTS---------------------------------

int main()
{
	char *test = "echo 'hello world'";
	t_token_builder *tokens = ft_tokenizer(test);

	while (tokens)
	{
		printf("Token: %s\n", tokens->buf);
		tokens = tokens->next;
	}
	return 0;
}

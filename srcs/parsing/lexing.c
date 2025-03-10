#include "../minishell.h"

void	ft_get_quotes(t_token_builder **builder, char *line, int start)
{
	int	curs;
	t_token_builder	*last;

	if (!line)
		return (NULL);

	if (line[start] == '\'')
		curs = ft_get_pos(line, ++start, '\'');
	else if (line[start] == '\"')
		curs = ft_get_pos(line, ++start, '\"');

	last = *builder;
	while (last)
		last = last->next;
	last->next = ft_calloc(sizeof(t_token_builder), 1);
	if (!last->next)
		return ; // free
	//ft_strndup(line, start, curs - start);
	if (curs - start >= LEX_BUFF_SIZE)
	{

	}
	else
	{
		while (start < curs && line[start])
		{
			last->next->buf[]
		}
	}
}





void	ft_addchar_to_token(t_token_builder **builder, char c)
{
	t_token_builder	*last;

	if (!*builder)
	{
		*builder = malloc(sizeof(t_token_builder));
		if (!*builder)
			return (NULL);
		(*builder)->len = 1;
		(*builder)->buf[0] = c;
		(*builder)->next = NULL;
		return ;
	}
	last = *builder;
	while (last)
		last = last->next;
	if (last->len >= LEX_BUFF_SIZE)
	{
		last->next = malloc(sizeof(t_token_builder));
		if (!last->next)
			return ; // faire une fonction pour free toute la liste
		last = last->next;
		last->len = 0;
		last->next = NULL;
	}
	last->buf[last->len + 1] = c;
}






//* State machine
//		* Normal : add char by char to buf
//		* Quotes : take all btw quotes and add it to buf
t_token_builder	*ft_tokenizer(char *line)
{
	t_token_builder	*tokens;
	int				i;

	if (!ft_check_pair(line, '\'') || !ft_check_pair(line, '\"'))
		return (NULL);

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			ft_get_quotes(line, i);
		
		i++;
	}

	return (tokens);
}




//!-------------------------TESTS---------------------------------

int main()
{
	char *test = "echo 'hello world'";
	t_list *tokens = ft_tokenizer(test);

	while (tokens)
	{
		printf("Token: %s\n", ((t_ast *)tokens->content)->cmd);
		tokens = tokens->next;
	}
	return 0;
}

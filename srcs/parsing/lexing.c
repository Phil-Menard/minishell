#include "../minishell.h"

// part of tokenizer
static void	space_handler(t_token_builder *tokens, char *line, int *i)
{
	while (line[*i] && line[*i] == ' ')
		(*i)++;
	if (tokens->buf != NULL)
		get_last(tokens)->next = new_tkb(0, NULL);
}

//* for double quotes, cpy quoted and take value (if) var
static char	*quotes(char *str, int start)
{
	char	*res;
	char	*var;
	int		size;
	int		iv;

	var = NULL;
	size = get_pos(str, start, '\"');
	res = ft_calloc(sizeof(char), (size - start));
	if (!res)
		return (NULL);
	while (str[start] && start < size)
	{
		if (str[start] == '$')
		{
			iv = start + 1;
			while (str[iv] && iv < size && str[iv] != ' '
				&& (str[iv] <= 9 || str[iv] >= 13))
				var = ft_straddchar(var, str[iv++]); //pb pour recup la var
			res = ft_straddstr(res, getenv(var));
			start = ft_strlen(getenv(var)) + iv;
			free(var);
			var = NULL;
		}
		res = ft_straddchar(res, str[start++]);
	}
	return (res);
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
	last = get_last(*builder);
	if (!last)
		return (0);
	size = 0;

	if (line[start - 1] == '\'')
	{
		size = get_pos(line, start, '\'') - start;
		quoted = ft_strndup(line, start, size);
	}
	else if (line[start - 1] == '\"')
	{
		quoted = quotes(line, start);
		size = ft_strlen(quoted);
	}
	if (!quoted)
		return (0);

	printf("prout\n");
	last->buf = ft_straddstr(last->buf, quoted);
	printf("prout2\n");
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

int	main(void)
{
	char			*test = "            <Makefile \"grep echo \"e abc | \"$test |a\"";

	if (!check_pair(test, '\'') || !check_pair(test, '\"'))
	{
		printf("Error odd nb of quotes.\n");
		return 1;
	}
	printf("str : %s\n", test);
	t_token_builder	*tokens = tokenizer(test);
	t_token_builder	*tmp;

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
}

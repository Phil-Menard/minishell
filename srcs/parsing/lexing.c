#include "../minishell.h"

static void printlist(t_token_builder *tokens)
{
	while (tokens)
	{
		if (tokens->buf)
			printf("%s", tokens->buf);
		if (tokens->next)
			printf(",");
		tokens = tokens->next;
	}
	printf("\n");
}

// add var to res
static void addvar(char **res, char *str, size_t *start, t_env *env)
{
	char	*var;
	char	*var_content;

	var = NULL;
	var_content = NULL;
	(*start)++;
	while (str[*start] && str[*start] != '\"'
		&& str[*start] != ' ' && (str[*start] <= 9 || str[*start] >= 13))
	{
		var = ft_straddchar(var, str[*start]);
		printf("line[%zu] = %c\n", *start, str[*start]);
		(*start)++;
	}
	var_content = ft_getenv(env, var);
	*res = ft_straddstr(*res, var_content);
	free(var_content);
	var_content = NULL;
	free(var);
	var = NULL;
}

//* for double quotes, cpy quoted and take value (if) var
static char	*quotes(char *str, size_t start, t_env *env)
{
	char	*res;

	res = NULL;
	while (str[start] && start < get_pos(str, start, '\"'))
	{
		if (str[start] == '$')
			addvar(&res, str, &start, env);
		else
			res = ft_straddchar(res, str[start++]);
	}
	return (res);
}

//* Add all quoted text in buf into list token_builder.
//* Return size of quoted text.
static size_t	addquotes_to_token(t_token_builder **builder, char *line, size_t start, t_env *env)
{
	size_t		size;
	char	*quoted;

	if (!line)
		return (0);
	size = 0;
	quoted = NULL;
	if (line[start - 1] == '\'')
	{
		size = get_pos(line, start, '\'') - start;
		quoted = ft_strndup(line, start, size);
	}
	else if (line[start - 1] == '\"')
	{
		quoted = quotes(line, start, env);
		size = ft_strlen(quoted);
	}
	if (!quoted)
		return (0);
	get_last(*builder)->buf = ft_straddstr(get_last(*builder)->buf, quoted);
	return (free(quoted), size);
}

// part of tokenizer
static void	space_handler(t_token_builder *tokens, char *line, size_t *i)
{
	t_token_builder	*last;

	last = get_last(tokens);
	while (line[*i] && line[*i] == ' ')
		(*i)++;
	if (tokens->buf != NULL) // to avoid create a null node when begin by space
		last->next = new_tkb(0, NULL);
}

//* State machine
//		* Normal : add char by char to token, split on spaces
//		* Quotes : take all btw quotes and add it to token
t_token_builder	*tokenizer(char *line, t_env *env)
{
	t_token_builder	*tokens;
	size_t			i;
	size_t			quote_count;

	i = 0;
	quote_count = 0;
	tokens = new_tkb(0, NULL);
	printf("line : %s\n", line);
	while (line[i] && i < ft_strlen(line))
	{
		printf("line[%zu] = %c\n", i, line[i]);
		if (line[i] == '\'' || line[i] == '\"')
		{
			i++;
			if (++quote_count % 2 != 0)
				i += addquotes_to_token(&tokens, line, i, env);
		}
		else if (line[i] && line[i] == ' ')
			space_handler(tokens, line, &i);
		else if (line[i])
		{
			if (line[i] == '$')
				addvar(&get_last(tokens)->buf, line, &i, env);
			else
				get_last(tokens)->buf = ft_straddchar(get_last(tokens)->buf, line[i++]);
		}
		printlist(tokens);
	}
	return (tokens);
}

//-------------------------TESTS---------------------------------

// To test lexing : cc -g -Wall -Wextra -Werror ../../libft/*.c ../utils/utils_2.c ../utils/utils.c lexing.c lexing_utils.c

/* int	main(void)
{
	char			*test = "            <Makefile \"grep echo \"e abc | \"$PWD |a\" | ls";
	t_token_builder	*tokens;
	t_token_builder	*tmp;

	if (!check_pair(test, '\'') || !check_pair(test, '\"'))
	{
		printf("Error odd nb of quotes.\n");
		return 1;
	}
	tokens = tokenizer(test);
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

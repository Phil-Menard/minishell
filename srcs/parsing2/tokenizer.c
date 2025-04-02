// #include "../minishell.h"

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <limits.h>

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_OPERATOR
}	t_token_type;

typedef struct s_token
{
	char			*content;
	t_token_type	type;
	struct s_token	*next;
}					t_token;

static size_t	ft_strlen(const char *s)
{
	size_t	size;

	size = 0;
	while (s[size])
		size++;
	return (size);
}

static char	*ft_strdup(const char *s)
{
	char	*dst;
	int		i;

	dst = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dst[i] = s[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

//add a char at the end of s1 (kind of realloc)
static char	*ft_straddchar(char *str, char c)
{
	char	*res;
	int		i;

	if (!str)
	{
		res = malloc(sizeof(char) * 2);
		if (!res)
			return (NULL);
		res[0] = c;
		res[1] = 0;
		return (res);
	}
	res = malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (!res)
		return (NULL);
	i = -1;
	while (str[++i])
		res[i] = str[i];
	res[i++] = c;
	res[i] = 0;
	free(str);
	return (res);
}

//////////////////////////////////////////////////////////////////////////////////////!

static void	add_token(t_token **tokens, char *buffer, t_token_type type)
{
	t_token	*new_token;
	t_token	*tmp;
	
	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return ;
	new_token->content = buffer;
	new_token->type = type;
	new_token->next = NULL;
	if (*tokens == NULL)
		*tokens = new_token;
	else
	{
		tmp = *tokens;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_token;
	}
}

static void	add_operator(t_token **tokens, char *line, int *i)
{
	if (line[*i] == '>' && line[*i + 1] == '>')
	{
		add_token(tokens, ft_strdup(">>"), TOKEN_OPERATOR);
		(*i)++;
	}
	if (line[*i] == '<' && line[*i + 1] == '<')
	{
		add_token(tokens, ft_strdup("<<"), TOKEN_OPERATOR);
		(*i)++;
	}
	else
		add_token(tokens, ft_strdup("|"), TOKEN_OPERATOR);
}

static inline void	add(t_token *tokens, char *buffer)
{
	if (buffer)
	{
		add_token(&tokens, ft_strdup(buffer), TOKEN_WORD);
		free(buffer);
		buffer = NULL;
	}
}

t_token	*tokenizer(char *line)
{
	t_token	*tokens;
	int		i;
	int		in_quote;
	char	*buffer;

	tokens = NULL;
	i = -1;
	in_quote = 0;
	buffer = NULL;
	while (line[++i])
	{
		if ((line[i] == ' ' || (line[i] >= 9 && line[i] <= 13)) && !in_quote)
			add(tokens, buffer);
		else if (line[i] == '<' || line[i] == '>' || line[i] == '|')
		{
			add(tokens, buffer);
			add_operator(&tokens, line, &i);
		}
		else if (line[i] == '\"' || line[i] == '\'')
			in_quote = !in_quote;
		else
			buffer = ft_straddchar(buffer, line[i]);
	}
	add(tokens, buffer);
	return (tokens);
}

////////////////////////////////////////////////////////////////! 

static void	putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
	write(1, "\n", 1);
}

static void	printlist(t_token *tokens)
{
	while (tokens)
	{
		putstr(tokens->content);
		tokens = tokens->next;
	}
}

static void	free_tokens(t_token **tokens)
{
	t_token	*tmp;
	size_t	i;

	i = -1;
	while (tokens[++i])
	{
		tmp = tokens[i]->next;
		free(tokens[i]->content);
		tokens[i]->content = NULL;
		free(tokens[i]);
		tokens[i] = tmp;
	}
}

int main(int ac, char **av)
{
	if (ac != 2)
		return (putstr("error nb arg\n"), 1);
	t_token	*tokens = tokenizer(av[1]);
	printlist(tokens);
	free_tokens(&tokens);
	return (0);
}
#include "minishell.h"

void	handle_var(char *str, int *x)
{
	char	*var;
	char	*res;
	int		i;
	int		j;

	i = *x;
	j = 0;
	while (str[i] != '\0' && str[i] != ' ' && str[i] != '"' && str[i] != '\n')
	{
		j++;
		i++;
	}
	var = ft_substr(str, *x, j);
	*x = i - 1;
	res = getenv(var);
	if (res)
	{
		i = 0;
		while (res[i])
		{
			write(1, &res[i], 1);
			i++;
		}
	}
	free(var);
}

void	echo_loop(char *str, int i, int quote)
{
	while (str[i])
	{
		if (str[i] == '"')
			quote++;
		else if (str[i] == '$')
		{
			i++;
			handle_var(str, &i);
		}
		else
			write(1, &str[i], 1);
		i++;
	}
}

void	ft_echo(char *str)
{
	int	i;
	int	option;
	int	quote;

	quote = 0;
	option = 0;
	if (ft_strncmp(str, "echo -n", 7) == 0)
	{
		i = 7;
		option = 1;
	}
	else
		i = 5;
	echo_loop(str, i, quote);
	if (option == 0)
		printf("\n");
}

#include "../minishell.h"

void	handle_var(char *str, int *x, int fd)
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
		ft_putstr_fd(res, fd);
	free(var);
}

void	echo_loop(char *str, int i, int fd, int option)
{
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			handle_var(str, &i, fd);
		}
		else
		{
			ft_putchar_fd(str[i], fd);
		}
		i++;
	}
	if (option == 0)
		ft_putchar_fd('\n', fd);
}

void	ft_echo(char *str, int fd)
{
	int		i;
	int		option;
	char	*line;

	option = 0;
	if (ft_strncmp(str, "echo -n", 7) == 0)
	{
		i = 8;
		option = 1;
	}
	else
		i = 5;
	line = str_without_redir(str);
	echo_loop(line, i, fd, option);
	free(line);
}

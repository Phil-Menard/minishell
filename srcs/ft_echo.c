#include "minishell.h"

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

void	echo_loop(char *str, int i, int fd)
{
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			handle_var(str, &i, fd);
		}
		else
			ft_putchar_fd(str[i], fd);
		i++;
	}
}

void	ft_echo(char *str)
{
	int		i;
	int		option;
	int		fd;
	char	*fd_name;

	fd = 1;
	option = 0;
	if (ft_strncmp(str, "echo -n", 7) == 0)
	{
		i = 8;
		option = 1;
	}
	else
		i = 5;
	fd_name = get_outfile(str);
	if (is_redirected(str) == 2)
		fd = open(fd_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	echo_loop(str, i, fd);
	if (option == 0)
		printf("\n");
}

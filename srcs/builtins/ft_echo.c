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

//check if arg is only -n (multiple n can be written) or different
int	check_arg(char *str)
{
	int	i;

	if (str[0] != '-')
		return (0);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (i);
}

void	ft_echo(char *str, int fd)
{
	char	**arr;
	char	*line;
	int		i;
	int		j;
	int		option;

	option = 0;
	arr = ft_split(str, " ");
	j = check_arg(arr[1]);
	if (j > 0)
	{
		i = 6 + j;
		option = 1;
	}
	else
		i = 5;
	line = str_without_redir(str);
	echo_loop(line, i, fd, option);
	free_db_array(arr);
	free(line);
}

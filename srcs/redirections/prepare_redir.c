#include "../minishell.h"

//check if there is a redirection
int	is_redirected(char *str)
{
	if (find_occurences(str, '<') == 1)
	{
		if (find_occurences(str, '>') == 1)
			return (0);
		else if (find_occurences(str, '>') == 2)
			return (4);
		else
			return (1);
	}
	else if (find_occurences(str, '>') > 0)
	{
		if (find_occurences(str, '>') == 1)
			return (2);
		else
			return (3);
	}
	else
		return (-1);
}

//return line without redirection
char	*str_without_redir(char *str)
{
	char	**arr;
	char	*res;
	int		i;

	arr = ft_split(str, " ");
	i = 0;
	res = NULL;
	while (arr[i])
	{
		if (find_occurences(arr[i], '<') == 0
			&& find_occurences(arr[i], '>') == 0)
		{
			if (res)
				res = ft_straddchar(res, ' ');
			res = ft_straddstr(res, arr[i]);
		}
		else
			i++;
		if (arr[i] != NULL)
			i++;
	}
	free_db_array(arr);
	return (res);
}

//get infile name
char	*get_infile(char *str)
{
	char	**arr;
	char	*res;
	int		i;

	arr = ft_split(str, " ");
	i = 0;
	res = NULL;
	while (arr[i])
	{
		if (find_occurences(arr[i], '<') > 0)
		{
			i++;
			res = ft_strdup(arr[i]);
			free_db_array(arr);
			return (res);
		}
		i++;
	}
	free_db_array(arr);
	return (res);
}

//get outfile name
char	*get_outfile(char *str)
{
	char	**arr;
	char	*res;
	int		i;

	arr = ft_split(str, " ");
	i = 0;
	res = NULL;
	while (arr[i])
	{
		if (find_occurences(arr[i], '>') > 0)
		{
			i++;
			res = ft_strdup(arr[i]);
			free_db_array(arr);
			return (res);
		}
		i++;
	}
	free_db_array(arr);
	return (res);
}

void	prepare_redir(char *str, int redirection, int *fd, int id)
{
	char	*path;
	char	**arg;
	char	*line;

	line = str_without_redir(str);
	path = get_right_path(line);
	arg = fill_arg(path, line);
	free(line);
	if (redirection >= 0)
		exec_redir(path, arg, fd, id);
	free_db_array(arg);
	free(path);
}

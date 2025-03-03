#include "minishell.h"

//CHECK IF THERE IS A REDIRECTION
int	is_redirected(char *str)
{
	if (find_occurences(str, '<') > 0 && find_occurences(str, '>') > 0)
		return (0);
	else if (find_occurences(str, '<') > 0 && find_occurences(str, '>') == 0)
		return (1);
	else if (find_occurences(str, '<') == 0 && find_occurences(str, '>') > 0)
	{
		if (find_occurences(str, '>') == 2)
			return (3);
		else
			return (2);
	}
	else
		return (-1);
}

//RETURN LINE WITHOUT REDIRECTION
char	*str_without_redir(char *str)
{
	char	**arr;
	char	*res;
	int		i;

	arr = ft_split(str, ' ');
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

//GET INFILE NAME
char	*get_infile(char *str)
{
	char	**arr;
	char	*res;
	int		i;

	arr = ft_split(str, ' ');
	i = 0;
	res = NULL;
	while (arr[i])
	{
		if (find_occurences(arr[i], '<') == 0)
		{
			i++;
			res = ft_strdup(arr[i]);
			free_db_array(arr);
			return (res);
		}
		i++;
	}
	free_db_array(arr);
	free(str);
	return (res);
}

//GET OUTFILE NAME
char	*get_outfile(char *str)
{
	char	**arr;
	char	*res;
	int		i;

	arr = ft_split(str, ' ');
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
	free(str);
	return (res);
}

void	prepare_redir(char *str, int redirection)
{
	char	*path;
	char	**arg;
	char	*line;

	line = str_without_redir(str);
	path = get_right_path(line);
	arg = fill_arg(path, line);
	free(line);
	if (redirection == 0)
		redir_in_and_out(str, path, arg);
	else if (redirection == 1)
		redir_input(str, path, arg);
	else if (redirection == 2)
		redir_output(str, path, arg);
	else if (redirection == 3)
		redir_output_append(str, path, arg);
	free_db_array(arg);
	free(path);
}

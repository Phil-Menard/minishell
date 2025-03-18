#include "../minishell.h"

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
		if (find_occurences(arr[i], '<') == 1)
		{
			i++;
			if (res)
			{
				free(res);
				res = NULL;
			}
			res = ft_strdup(arr[i]);
		}
		i++;
	}
	free_db_array(arr);
	return (res);
}

//get outfile name
char	**get_outfile(char *str)
{
	char	**arr;
	char	**res;
	int		i;
	int		j;

	arr = ft_split(str, " ");
	i = 0;
	j = 0;
	res = malloc((find_occurences(str, '>') + 1) * sizeof(char *));
	while (arr[i])
	{
		if (find_occurences(arr[i], '>') > 0)
		{
			i++;
			res[j] = ft_strdup(arr[i]);
			j++;
		}
		i++;
	}
	free_db_array(arr);
	res[j] = NULL;
	return (res);
}

void	prepare_redir(t_var *vars, int redirection, int *fd, t_env **env)
{
	char	**arg;
	char	*line;

	line = str_without_redir(vars->content);
	vars->path = get_right_path(line);
	arg = fill_arg(vars->path, line);
	free(line);
	if (redirection >= 0)
		exec_redir(vars, arg, fd, env);
	free_db_array(arg);
	free(vars->path);
}

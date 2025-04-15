/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmenard <pmenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:10:06 by lefoffan          #+#    #+#             */
/*   Updated: 2025/04/11 16:32:40 by pmenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//return the size of a 2D array
int	double_arr_len(char **arr)
{
	int	size;

	size = 0;
	while (arr[size])
		size++;
	return (size);
}

//compare 2 strings
//0 if same
//1 if different
int	ft_cmpstr(char *s1, char *s2)
{
	if (ft_strlen(s1) == ft_strlen(s2))
	{
		if (ft_strncmp(s1, s2, ft_strlen(s1)) == 0)
			return (0);
	}
	return (1);
}

void	print_multiple_strfd(char *s1, char *var, char *s2)
{
	ft_putstr_fd(s1, 1);
	ft_putstr_fd(var, 1);
	ft_putstr_fd(s2, 1);
}

void	start_loop(t_var *vars, t_env **env)
{
	vars->prompt = set_prompt_arg(env);
	vars->line = readline(vars->prompt);
	update_status(vars, env);
}

char	*path_with_way(char *str, t_var *vars)
{
	char	*path;

	path = get_next_path(NULL, str, vars);
	if (path && find_occurences(path, '/') != 0)
		return (path);
	return (NULL);
}

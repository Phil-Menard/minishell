/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmenard <pmenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:09:17 by lefoffan          #+#    #+#             */
/*   Updated: 2025/04/16 14:14:24 by pmenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//set arr variable for get_right_path
char	**split_path_var(t_env **env)
{
	char	**arr;
	char	*temp;

	arr = NULL;
	temp = NULL;
	temp = ft_getenv(*env, "PATH");
	if (temp)
		arr = ft_split(temp, ":");
	free(temp);
	return (arr);
}

void	end_right_path(t_var *vars, char *str, char **arr)
{
	if (find_occurences(str, '/') == 0)
	{
		vars->exit_statut = 127;
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	if (arr)
		free_db_array(arr);
}

//print a message when permission is denied, and update exit statut
void	errno_error(t_var *vars)
{
	ft_putstr_fd("Permission denied\n", 2);
	vars->exit_statut = 126;
}

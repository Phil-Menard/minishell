/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:09:17 by lefoffan          #+#    #+#             */
/*   Updated: 2025/04/11 11:10:42 by lefoffan         ###   ########.fr       */
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
	vars->exit_statut = 127;
	if (ft_strrchr(str, '/') == NULL)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	if (arr)
		free_db_array(arr);
}

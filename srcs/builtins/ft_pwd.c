/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:09:04 by lefoffan          #+#    #+#             */
/*   Updated: 2025/04/11 11:10:42 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(t_var *vars, int fd)
{
	char	*path;

	path = getcwd(NULL, 0);
	path = ft_straddchar(path, '\n');
	if (path)
	{
		ft_putstr_fd(path, fd);
		free(path);
		vars->exit_statut = 0;
	}
	else
	{
		perror("path error");
		vars->exit_statut = 1;
	}
}

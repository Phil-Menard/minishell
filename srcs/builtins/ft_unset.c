/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:09:08 by lefoffan          #+#    #+#             */
/*   Updated: 2025/04/11 11:10:42 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_unset(t_env **env, t_env **export, t_var *vars)
{
	int		i;
	int		size;

	size = ft_strlen("declare -x ");
	i = 1;
	while (vars->cmd_line[vars->i].args[i])
	{
		*env = remove_env_var(env, vars->cmd_line[vars->i].args[i], 0);
		*export = remove_env_var(export, vars->cmd_line[vars->i].args[i], size);
		i++;
	}
	vars->exit_statut = 0;
}

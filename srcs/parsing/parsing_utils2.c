/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:16:50 by lefoffan          #+#    #+#             */
/*   Updated: 2025/04/18 18:31:54 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_mod	is_protected(char c)
{
	static t_mod	mod = MOD_NORMAL;

	if (mod == MOD_NORMAL && c == '"')
		mod = MOD_DOUBLE;
	else if (mod == MOD_NORMAL && c == '\'')
		mod = MOD_SINGLE;
	else if (mod == MOD_SINGLE && c == '\'')
		mod = MOD_NORMAL;
	else if (mod == MOD_DOUBLE && c == '"')
		mod = MOD_NORMAL;
	return (mod);
}

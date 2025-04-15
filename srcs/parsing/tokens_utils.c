/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:09:53 by lefoffan          #+#    #+#             */
/*   Updated: 2025/04/15 19:27:17 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*new_token(char *s, t_token_type type, t_token *next, t_expand exp)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->content = ft_strdup(s);
	new->type = type;
	new->expand = exp;
	new->next = next;
	return (new);
}

t_token	*last_token(t_token *tokens)
{
	t_token	*tmp;

	if (!tokens)
		return (NULL);
	tmp = tokens;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

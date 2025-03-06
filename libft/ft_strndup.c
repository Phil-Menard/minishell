/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 11:51:34 by lefoffan          #+#    #+#             */
/*   Updated: 2025/03/06 11:55:33 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, int start, size_t len)
{
	char	*dst;

	if (len > ft_strlen(s))
		return (NULL);
	dst = ft_calloc((len + 1), sizeof(char));
	if (!dst)
		return (NULL);
	while (start < len && s[start])
	{
		dst[start] = s[start];
		start++;
	}
	dst[start] = '\0';
	return (dst);
}
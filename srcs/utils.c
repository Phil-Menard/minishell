#include "minishell.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
	{
		len++;
	}
	return (len);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (!s1)
		return (1);
	while ((*s1 && *s2) && n > 0)
	{
		if (*s1 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
		n--;
	}
	if (n == 0)
		return (0);
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	i;
	size_t	size_left;
	size_t	s_len;

	s_len = ft_strlen(s);
	size_left = s_len - start;
	if (start >= s_len)
		len = 0;
	else if (len > size_left)
		len = s_len - start;
	ptr = malloc((len + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (len > 0 && size_left > 0)
	{
		ptr[i++] = s[start++];
		size_left--;
		len--;
	}
	ptr[i] = '\0';
	return (ptr);
}

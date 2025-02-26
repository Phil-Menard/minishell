#include "minishell.h"

char	*ft_strjoin_middle(char const *s1, char slash, char const *s2)
{
	char	*ptr;
	int		i;
	int		j;

	ptr = malloc((ft_strlen(s1) + 1 + ft_strlen(s2) + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = slash;
	i++;
	j = 0;
	while (s2[j])
	{
		ptr[i] = s2[j];
		i++;
		j++;
	}
	ptr[i] = '\0';
	return (ptr);
}

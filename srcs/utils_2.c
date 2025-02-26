#include "minishell.h"

void	free_db_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

// static int	ft_countnbstring(char const *s, char c)
// {
// 	int	i;
// 	int	count;

// 	i = 0;
// 	count = 0;
// 	while (s[i])
// 	{
// 		while (s[i] && s[i] == c)
// 			i++;
// 		if (s[i])
// 			count++;
// 		while (s[i] && s[i] != c)
// 			i++;
// 	}
// 	return (count);
// }

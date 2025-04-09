#include "../minishell.h"

//return the size of a 2D array
int	double_arr_len(char **arr)
{
	int	size;

	size = 0;
	while (arr[size])
		size++;
	return (size);
}

//compare 2 strings
//0 if same
//1 if different
int	ft_cmpstr(char *s1, char *s2)
{
	if (ft_strlen(s1) == ft_strlen(s2))
	{
		if (ft_strncmp(s1, s2, ft_strlen(s1)) == 0)
			return (0);
	}
	return (1);
}

void	print_multiple_strfd(char *s1, char *var, char *s2)
{
	ft_putstr_fd(s1, 1);
	ft_putstr_fd(var, 1);
	ft_putstr_fd(s2, 1);
}

#include "../minishell.h"

// find s2 in s1
// return 1 if founded or 0 if not find
int	ft_strfind(char *s1, char *s2)
{
	int	i;
	int	j;
	int	s2_size;

	i = 0;
	s2_size = ft_strlen(s2);
	while (s1[i])
	{
		j = 0;
		if (s1[i] == s2[j])
		{
			while (s1[i] == s2[j])
			{
				j++;
				i++;
			}
			if (j == s2_size)
				return (1);
		}
		else
			i++;
	}
	return (0);
}

//return the size of a 2D array
int	double_arr_len(char **arr)
{
	int	size;

	size = 0;
	while (arr[size])
		size++;
	return (size);
}

void	quit(char *msg, int exit_status, t_var *vars)
{
	if (msg)
		ft_putstr_fd(msg, 2);
	vars->exit_statut = exit_status;
	// exit(vars->exit_statut);
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

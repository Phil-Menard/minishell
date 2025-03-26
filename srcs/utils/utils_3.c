#include "../minishell.h"

int	ft_str_isalpha(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}

long int	ft_atol(char *nptr)
{
	long int	res;
	int			sign;

	res = 0;
	sign = 1;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == ' ')
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign *= -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		res = (res * 10) + (*nptr - '0');
		nptr++;
	}
	return (res * sign);
}

static size_t	ft_int_len(long int n)
{
	size_t	size;

	if (n == 0)
		return (1);
	size = 0;
	if (n < 0)
	{
		size++;
		n *= -1;
	}
	while (n)
	{
		size++;
		n /= 10;
	}
	return (size);
}

char	*ft_ltoa(long int n)
{
	char		*res;
	size_t		len;
	size_t		i;
	long int	nbr;

	i = 0;
	nbr = n;
	len = ft_int_len(nbr);
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	if (nbr < 0)
	{
		nbr *= -1;
		res[0] = '-';
		i = 1;
	}
	res[len] = '\0';
	while (len > i)
	{
		res[--len] = '0' + (nbr % 10);
		nbr /= 10;
	}
	return (res);
}

void	init_vars(t_var *vars)
{
	vars->arg = NULL;
	vars->arr = NULL;
	vars->cmd = NULL;
	vars->cmd_split = NULL;
	vars->exit_statut = 0;
	vars->i = 0;
	vars->line = NULL;
	vars->path = NULL;
	vars->pids = NULL;
	vars->prompt = NULL;
	vars->size_cmd = 0;
}

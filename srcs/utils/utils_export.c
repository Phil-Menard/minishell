#include "../minishell.h"

int	var_already_exist(t_env **export, char *str)
{
	t_env	*current;

	current = *export;
	while (current)
	{
		if (ft_strncmp(current->var + 11, str, ft_strlen(str)) == 0)
			return (1);
		current = current->next;
	}
	return (0);
}

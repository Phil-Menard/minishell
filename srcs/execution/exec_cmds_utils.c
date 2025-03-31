#include "../minishell.h"

//set arr variable for get_right_path
char	**set_arr_right_path(t_env **env)
{
	char	**arr;
	char	*temp;

	arr = NULL;
	temp = NULL;
	temp = ft_getenv(*env, "PATH");
	if (temp)
		arr = ft_split(temp, ":");
	free(temp);
	return (arr);
}

void	end_right_path(t_var *vars, char *str, char **arr)
{
	vars->exit_statut = 127;
	if (ft_strrchr(str, '/') == NULL)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	if (arr)
		free_db_array(arr);
}

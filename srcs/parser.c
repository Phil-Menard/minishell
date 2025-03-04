# include "minishell.h"

char	ft_gettokken()
{
	
}

void	ft_parse(char *line, t_env *env, int *exit_code)
{
	t_tree	*tree;
	char	**split;
	char	*str;
	int		count;

	split = ft_split(line, " \t\n\r\v\f");
	count = 0;
	str = NULL;
	while (split[count])
	{
		str = ft_straddstr(str, split[count]);
		if (split[count + 1])
			str = ft_straddchar(str, ' ');
		count++;
	}
	free_db_array(split);
	tree = ft_new_node(str);
	// printf("tree->cmd : %s\n", tree->cmd);
	builtins(tree->cmd, env, exit_code);
	free(str);
	ft_free_list(tree);
}

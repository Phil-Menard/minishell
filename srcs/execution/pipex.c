#include "../minishell.h"

char	*get_cmd_name(char *argv)
{
	char	**arr;
	char	*cmd;

	arr = ft_split(argv, ' ');
	cmd = ft_strdup(arr[0]);
	free_db_array(arr);
	return (cmd);
}

void	check_path_errors(char *argv, char **env, int *pipefd)
{
	char	*path;

	close(*pipefd);
	path = get_right_path(env, argv);
	if (!path)
	{
		path = get_cmd_name(argv);
		ft_putstr_fd(path, 2);
		free(path);
		ft_putstr_fd(": command not found\n", 2);
		free_db_array(argv);
		exit(EXIT_FAILURE);
	}
}

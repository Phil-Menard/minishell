#include "../minishell.h"

void	pipex(char **arr, t_env **env, int *fd)
{
	int		pipefd[2];
	int		previous_fd;
	int		i;
	pid_t	id;

	i = 0;
	while (arr[i])
	{
		fd = set_fd(arr[i], fd);
		if (i == 0)
			previous_fd = fd[0];
		else
		{
			if (fd[0] > 1)
				previous_fd = fd[0];
		}
		if (pipe(pipefd) == -1)
			return (perror("pipe"), exit(EXIT_FAILURE));
		id = fork();
		if (id == -1)
			return (perror("fork"), exit(EXIT_FAILURE));
		if (id == 0)
		{
			pipefd[0] = previous_fd;
			if (i == double_arr_len(arr) - 1)
				pipefd[1] = fd[1];
			find_correct_function(arr[i], pipefd, env, id);
		}
		previous_fd = pipefd[0];
		fd[0] = 1;
		fd[1] = 1;
		close(pipefd[1]);
		wait(NULL);
		i++;
	}
	close(pipefd[0]);
}

/* char	*get_cmd_name(char *argv)
{
	char	**arr;
	char	*cmd;

	arr = ft_split(argv, " ");
	cmd = ft_strdup(arr[0]);
	free_db_array(arr);
	return (cmd);
} */

/* void	check_path_errors(char *argv, char **env, int *pipefd)
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
} */

#include "../minishell.h"

char	**lst_to_arr(t_env **env)
{
	t_env	*current;
	char	**arr;
	int		size;
	int		i;

	current = *env;
	size = env_size(*env);
	arr = malloc((size + 1) * sizeof(char *));
	i = 0;
	while (current)
	{
		arr[i] = ft_strdup(current->var);
		i++;
		current = current->next;
	}
	arr[i] = NULL;
	return (arr);
}

void	ft_execve(char *path, char **arg, t_env **env)
{
	char	**arr_env;

	arr_env = lst_to_arr(env);
	if (execve(path, arg, arr_env) == -1)
	{
		perror(arg[0]);
		if (path)
			free(path);
		if (arg)
			free_db_array(arg);
		if (arr_env)
			free_db_array(arr_env);
		exit(EXIT_FAILURE);
	}
}

//check which cmd is entered in line, and call a builtin or execve
void	builtin_or_cmd(t_line *line, int *fd, t_env **env, t_env **exp)
{
	int	size;

	line->cmd_split = ft_split(line->content, " ");
	size = ft_strlen(line->cmd_split[0]);
	if (ft_strncmp(line->cmd_split[0], "pwd", size) == 0)
		ft_pwd(fd[1]);
	else if (ft_strncmp(line->content, "env", size) == 0)
		ft_env(*env, fd[1]);
	else if (ft_strncmp(line->content, "echo", size) == 0)
		ft_echo(line->content, fd[1]);
	else if (ft_strncmp(line->content, "cd", size) == 0)
		ft_cd(line->content, *env, fd[1]);
	else if (ft_strncmp(line->content, "unset", size) == 0)
		ft_unset(line->content, env, exp);
	else if (ft_strncmp(line->content, "export", size) == 0)
		ft_export(line->content, env, exp, fd[1]);
	else if (ft_strncmp(line->content, "exit", size) == 0)
		ft_exit(fd, line, env, exp);
	else
		exec_cmds(line->content, fd, env);
	close_multiple_fd(fd);
	free_db_array(line->cmd_split);
}

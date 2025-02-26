#include "minishell.h"

int	check_quote(char *str)
{
	int	i;
	int	quote;

	quote = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
			quote++;
		i++;
	}
	return (quote);
}

void	builtins(char *line, char **env, int *exit_code)
{
	if (ft_strncmp(line, "pwd", 3) == 0)
		ft_pwd(); // print actual working
	if (ft_strncmp(line, "env", 3) == 0)
		ft_env(env); // print the env
	if (ft_strncmp(line, "echo", 4) == 0)
		ft_echo(line);
	if (ft_strncmp(line, "cd", 2) == 0)
		ft_cd(line);
	if (ft_strncmp(line, "exit", 4) == 0)
		ft_exit(exit_code);
}

char	*get_lines(char *line)
{
	char	*new_line;
	char	*temp;
	char	*res;
	int		i;

	i = 0;
	new_line = readline(">");
	res = ft_strjoin(line, new_line);
	while (check_quote(new_line) % 2 == 0)
	{
		temp = ft_strdup(res);
		free(res);
		new_line = readline(">");
		res = ft_strjoin_middle(temp, '\n', new_line);
		free(temp);
	}
	free(new_line);
	return (res);
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	int		exit_code;

	(void) argc;
	(void) argv;
	(void) env;
	exit_code = 1;
	while (exit_code == 1)
	{
		line = readline(">");
		if (check_quote(line) % 2 != 0)
			line = get_lines(line);
		builtins(line, env, &exit_code);
	}
	return (0);
}

/*
work on mybranch (Leon || Phil)
push with git push origin mybranch
go to main (git checkout main)
update main (git pull origin main)
fusion branch (git merge mybranch)
push everything (git push origin main)
*/

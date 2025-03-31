#include "minishell.h"

void	print_minishell(void)
{
	printf("___  ________ _   _ _____ _____ _   _  _____ _      _     \n");
	printf("|  \\/  |_   _| \\ | |_   _/  ___| | | ||  ___| |    | |    \n");
	printf("| .  . | | | |  \\| | | | \\ `--.| |_| || |__ | |    | |    \n");
	printf("| |\\/| | | | | . ` | | |  `--. \\  _  ||  __|| |    | |    \n");
	printf("| |  | |_| |_| |\\  |_| |_/\\__/ / | | || |___| |____| |____\n");
	printf("\\_|  |_/\\___/\\_| \\_/\\___/\\");
	printf("____/\\_| |_/\\____/\\_____/\\_____/\n\n");
}

//check if vars contains a pipe or not, and call the corresponding function
void	check_pipes(t_var *vars, t_env **env, t_env **export)
{
	char	*temp;
	int		*fd;
	int		arr_size;

	fd = NULL;
	temp = parse_redirections(vars->line);
	free(vars->line);
	vars->line = ft_strdup(temp);
	free(temp);
	vars->arr = prepare_line(vars->line);
	if (!vars->arr[1])
	{
		fd = init_and_set_fd(vars->line);
		if (fd[0] > -1)
			builtin_or_cmd(vars, fd, env, export);
		else
			close_multiple_fd(fd);
	}
	else
	{
		free(vars->line);
		vars->line = NULL;
		arr_size = double_arr_len(vars->arr);
		pipex(vars, env, export, arr_size);
	}
	free_vars(vars);
	printf("status : %d\n", vars->exit_statut);
}

char	*set_prompt_arg(t_env **env)
{
	char	*prompt_arg;
	char	*user_name;
	char	*pwd;
	char	*dollar_sign;

	user_name = ft_getenv(*env, "USER");
	dollar_sign = ft_strdup("$ ");
	prompt_arg = ft_strjoin(user_name, ":");
	pwd = getcwd(NULL, 0);
	prompt_arg = ft_straddstr(prompt_arg, pwd);
	prompt_arg = ft_straddstr(prompt_arg, dollar_sign);
	free(user_name);
	free(dollar_sign);
	free(pwd);
	return (prompt_arg);
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
	t_env	*export;
	t_var	vars;

	(void) argc;
	(void) argv;
	env = NULL;
	export = NULL;
	fill_env(&env, envp);
	init_export_lst(&env, &export);
	init_vars(&vars);
	print_minishell();
	set_signal_action();
	while (1)
	{
		vars.prompt = set_prompt_arg(&env);
		vars.line = readline(vars.prompt);
		add_history(vars.line);
		if (ft_strlen(vars.line) > 0)
			parsing(&env, &vars, &export);
		if (!vars.line)
			free(vars.prompt);
	}
	free_env(env);
	free_env(export);
	rl_clear_history();
	return (0);
}

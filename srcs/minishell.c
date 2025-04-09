#include "minishell.h"

volatile sig_atomic_t	in_child = 0;

static void	print_minishell(void)
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
	int		*fd;

	fd = NULL;
	if (!vars->tokens)
		return ;
	if (vars->nb_cmd_line == 1)
	{
		vars->i = 0;
		fd = init_and_set_fd(vars->cmd_line, vars, env);
		if (vars->cmd_line[vars->i].cmd && fd[0] > -1)
			builtin_or_cmd(vars, fd, env, export);
		else
			close_multiple_fd(fd);
	}
	else if (vars->nb_cmd_line > 1)
	{
		vars->pids = malloc(sizeof(pid_t) * vars->nb_cmd_line);
		free(vars->line);
		vars->line = NULL;
		pipex(vars, env, export);
	}
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

void	init_minishell(t_env **env, t_env **export, t_var *vars, char **envp)
{
	fill_env(env, envp);
	init_export_lst(env, export);
	init_vars(vars);
	update_exit_env(*env, vars);
	print_minishell();
	set_signal_action();
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
	init_minishell(&env, &export, &vars, envp);
	while (1)
	{
		in_child = 0;
		vars.prompt = set_prompt_arg(&env);
		vars.line = readline(vars.prompt);
		if (in_child == 130 || in_child == 131)
		{
			vars.exit_statut = in_child;
			update_exit_env(env, &vars);
			in_child = 0;
		}
		if (vars.line == NULL)
			handle_ctrl_d(&env, &export, &vars);
		add_history(vars.line);
		if (ft_strlen(vars.line) > 0)
		{
			parser(&env, &vars, &export);
			free_vars(&vars);
		}
		else
			free(vars.prompt);
	}
	return (0);
}

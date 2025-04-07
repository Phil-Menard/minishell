#include "minishell.h"

volatile int unblock_sigquit = 0;

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
	size_t i = 0;
	int j;
	while (i < vars->nb_cmd_line)
	{
		j = 0;
		while (vars->cmd_line[i].infile[j])
		{
			printf("infile : %s\n", vars->cmd_line[i].infile[j]);
			j++;
		}
		j = 0;
		while (vars->cmd_line[i].outfile[j])
		{
			printf("outfile : %s\n", vars->cmd_line[i].outfile[j]);
			j++;
		}
		i++;
	}
	// temp = parse_redirections(vars->line);
	// free(vars->line);
	// vars->line = ft_strdup(temp);
	// free(temp);
	fd = init_and_set_fd(vars->cmd_line, vars, env);
	if (vars->nb_cmd_line == 1 && fd[0] > -1)
	{
		vars->i = 0;
		builtin_or_cmd(vars, fd, env, export);
	}
	else if (fd[0] != -1)
	{
		close_multiple_fd(fd);
		free(vars->line);
		vars->line = NULL;
		pipex(vars, env, export);
	}
	else
		close_multiple_fd(fd);
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
		vars.prompt = set_prompt_arg(&env);
		vars.line = readline(vars.prompt);
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
	free_env(env);
	free_env(export);
	rl_clear_history();
	return (0);
}

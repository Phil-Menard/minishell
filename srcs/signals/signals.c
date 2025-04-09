#include "../minishell.h"

//routine de gestin SIGINT
void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		if (in_child != 1)
			rl_redisplay();
		in_child = 130;
	}
}

void	set_signal_action(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = &sig_handler;
	sigaction(SIGINT, &act, NULL);
	if (in_child == 0)
		signal(SIGQUIT, SIG_IGN);
	sigaction(SIGPIPE, &act, NULL);
}

void	handle_ctrl_d(t_env **env, t_env **export, t_var *vars)
{
	free_env(*env);
	free_env(*export);
	free_vars(vars);
	rl_clear_history();
	ft_putstr_fd("exit\n", 1);
	exit(0);
}

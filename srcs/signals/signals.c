#include "../minishell.h"

//routine de gestin SIGINT
void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		if (g_exit_signal == 1)
		{
			printf("\n");
			rl_replace_line("", 0);
			rl_on_new_line();
			g_exit_signal = 130;
		}
		else if (g_exit_signal == 7)
			g_exit_signal = 130;
		else
		{
			printf("\n");
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
			g_exit_signal = 130;
		}
	}
}

void	set_signal_action(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = &sig_handler;
	act.sa_flags = SA_SIGINFO | SA_RESTART;
	sigaction(SIGINT, &act, NULL);
	if (g_exit_signal == 0)
		signal(SIGQUIT, SIG_IGN);
	else
		sigaction(SIGQUIT, &act, NULL);
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

int rl_custom_hook(void)
{
	if (g_exit_signal == 130)
		rl_done = 1;
	return (0);
}

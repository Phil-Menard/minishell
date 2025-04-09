#include "../minishell.h"

//routine de gestin SIGINT
void	sig_handler(int signal)
{
	printf("in_child : %d\n", in_child);
	if (signal == SIGINT)
	{
		if (in_child == 0)
		{
			printf("\n");
			rl_replace_line("", 0);
			rl_on_new_line();
		}
		else
			exit(130);
	}
	if (in_child == 1 && signal == SIGQUIT)
	{
		printf("Quit (Core dumped)\n");
		exit(203);
	}
}


void	set_signal_action(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = &sig_handler;
	sigaction(SIGINT, &act, NULL);
	if (in_child == 1)
		sigaction(SIGQUIT, &act, NULL);
	else
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

#include "../minishell.h"

//routine de gestin SIGINT
void	sigint_handler(int signal)
{
	if (signal == SIGINT)
		ft_putstr_fd("Intercepted SIGINT\n", 1);
}

void	set_signal_action(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = &sigint_handler;
	sigaction(SIGINT, &act, NULL);
}

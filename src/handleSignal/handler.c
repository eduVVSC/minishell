
#include "minishell.h"

// reset the signals whenever open the execve on child process

void signalHandler(int signum, siginfo_t *info, void *context)
{
	if (signum == SIGINT)
		cntrl_C();
	if (signum == SIGQUIT)
		cntrl_Backslash();

}

void	cntrl_C()
{
	char	*str;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	cntrl_Backslash()
{
	rl_on_new_line();
	rl_replace_line("    ", 0);
	rl_redisplay();
}

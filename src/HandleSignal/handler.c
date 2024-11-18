#include "minishell.h"

void signalHandler(int signum, siginfo_t *info, void *context)
{
	if (signum == SIGINT)
		cntrl_C();
	if (signum == SIGQUIT)
		cntrl_Backslash();

}

void	cntrl_C()
{
	rl_on_new_line();
	//rl_replace_line("", 0);  // Clear the current input line
	rl_redisplay();
//	rl_redisplay();
//	rl_on_new_line();
}

void	cntrl_Backslash()
{
	printf("Control back");
}

void	cntrl_D()
{
	printf("Control D used\n");
	exit(EXIT_SUCCESS);
}

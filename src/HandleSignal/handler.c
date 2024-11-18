#include "minishell.h"

void signalHandler(int signum, siginfo_t *info, void *context)
{
	printf("%d", signum);
	if (signum == SIGINT)
		cntrl_C();
	if (signum == EOF)
		cntrl_D();
	if (signum == SIGQUIT)
		cntrl_Backslash();

}

void	cntrl_C()
{
	printf("Control C used\n");
	rl_redisplay();
	rl_on_new_line();
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


# include "../includes/minishell.h"

void	cntrl_C()
{
	printf("Control C used\n");
}

void	cntrl_Backslash()
{
}

void	cntrl_D()
{
	printf("Control D used\n");
	exit(EXIT_SUCCESS);
}

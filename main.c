
#include "includes/minishell.h"


int	main(void)
{
	struct sigaction	sa;
	char	*prefix;
	char	*str;
	char	*pwd;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = &cntrl_D;
	sigaction(SIGINT, &sa, NULL);

	while(1)
	{
		pwd = getenv("PWD");
		prefix = ft_strjoin(pwd, ": ");
		str = readline(prefix);
		printf( "%s\n", str);
	}
	free(str);
	return 0;
}

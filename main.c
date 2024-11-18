
#include "includes/minishell.h"


int	main(void)
{
	t_env	*env_vars;
	struct	sigaction	sa;
	char	*prefix;
	char	*str;
	char	*pwd;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = &signalHandler;
	sigaction(SIGINT, &sa, NULL);
	
	sigaction(EOF, &sa, NULL);
	env_vars = malloc(sizeof(env_vars));
	while(1)
	{
		env_vars->pwd = getenv("PWD");
		prefix = ft_strjoin(env_vars->pwd, "$ ");
		str = readline(prefix);
		add_history(str);
	}
	free(str);
	return 0;
}

#include "minishell.h"

/* int	main(void)
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
	sigaction(SIGQUIT, &sa, NULL);

	// eu como merda
	// eu como merda
	// eu como merda
	env_vars = malloc(sizeof(env_vars));
	while(1)
	{
		env_vars->pwd = getenv("PWD"); // need to use protection
		prefix = ft_strjoin(env_vars->pwd, "$ ");
		str = readline(prefix);
		add_history(str);
	}
	free(str);
	return 0;
} */

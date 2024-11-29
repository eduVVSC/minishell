/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:14:53 by dioferre          #+#    #+#             */
/*   Updated: 2024/11/25 17:02:14 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

int	main(int ac, char **av,char **envp)
{
	t_env		*env_vars;
	t_tokens	*tokens;
	char	*input;

	struct	sigaction	sa;
	(void) ac;
	(void) av;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = &signalHandler;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);

	env_vars = malloc(sizeof(env_vars));
	while(1)
	{
		env_vars->pwd = getenv("PWD"); // need to use protection
		if (!env_vars->pwd)
			env_vars->pwd = "";
		env_vars->prefix = ft_strjoin(env_vars->pwd, "$ ");
		input = readline(env_vars->prefix);
		tokens = get_tokens(input);
		if (tokens == NULL)
			exit(EXIT_SUCCESS);
		print_tokens(tokens); //action
		handle_commands(tokens, env_vars, envp);
		add_history(input);
	}
	return 0;

}

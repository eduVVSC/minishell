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

#include "minishell.h"


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
		env_vars->prefix = ft_strjoin(env_vars->pwd, "$ ");
		input = readline(env_vars->prefix);
		tokens = get_tokens(input);
		if (tokens == NULL)
			exit(EXIT_SUCCESS);
		handle_commands(tokens, env_vars, envp);
		//print_tokens(tokens); //action
		add_history(input);
	}
	return 0;

}
/*
int	main(int argc, char **argv)
{
	t_tokens *tokens;
	char *input = argv[1];
	int	i = 0;
	tokens = get_tokens(input);
	print_tokens(tokens);
	t_tokens *tmp;
	while (tokens)
	{
		tmp = tokens->next;
		free (tokens->token);
		free (tokens);
		tokens = tmp;
	}
}
 */

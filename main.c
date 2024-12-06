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

void test_expand(t_tokens *tokens)
{
	printf("------------------------------\n");
	printf("\tafter the handle quotes\n");
	printf("------------------------------\n");
	while(tokens != NULL)
	{
		expand_token(tokens);
		tokens = tokens->next;
	}
}

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
		print_tokens(tokens); //action
		//test_expand(tokens);
		print_tokens(tokens); //action
		add_history(input);
	}
	return 0;
}

/* ---test heardock*/
/* int	main(int ac, char **av,char **envp)
{
	t_heredock *heredock;
	t_heredock *node1;
	t_heredock *node2;

	heredock = malloc(sizeof(t_heredock));
	node1 = malloc(sizeof(t_heredock));
	node2 = malloc(sizeof(t_heredock));

	heredock->key = "1";
	node1->next = node1;
	node1->key = "2";
	node1->next = NULL;
	node2->key = "2";
	node2->next = NULL;

	heredock = doing_heredock(heredock);
	printf("%s\n", heredock->fullinput_until_key);
	return (0);
}
 */

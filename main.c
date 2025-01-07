/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:14:53 by dioferre          #+#    #+#             */
/*   Updated: 2025/01/05 18:22:36 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Set the signals actions in the program
void	setting_signals()
{
	struct	sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = &signalHandler;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

/// @brief Run the shell implementations
/// @param shell
void	runnnig_shell(t_shell *shell)
{
	char	*input;

	while (1)
	{
		input = readline(shell->dir_now);
		add_history(input);
		if (check_input(shell, input) == 0)
		{
			shell->tokens = get_tokens(shell ,input);
			//print_tokens(shell->tokens);
			make_tree(shell);
			clean_next_round(shell);
		}
		free(input);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_shell		*shell;

	setting_signals();
	shell = setting_shell(ac, av, envp);
	if (!shell)
		exit (ft_printf("Program closing! Could not set shell\n"));
	runnnig_shell(shell);
	return (0);
}

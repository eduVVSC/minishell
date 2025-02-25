/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:14:53 by dioferre          #+#    #+#             */
/*   Updated: 2025/02/25 14:14:34 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig_sign = 0;

/// @brief Set the signals actions in the program
void	setting_signals(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = &signalHandler;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

/// @brief Function check if the last character of the user's input is a
/// @brief |, if so will display a readline and concatnate it to the old input
/// @param input
/// @return (new_input if end in '|')  (old_input if doesn't end in '|')
char	*check_last_character(char	*input)
{
	char	*next_input;
	int		i;

	i = ft_strlen(input);
	while (--i > 0)
		if (input[i] != ' ' && input[i] != '\t' && input[i] != '\n')
			break ;
	if (input[i] == '|')
	{
		next_input = readline(">");
		if (!next_input)
		{
			free(input);
			input = NULL;
			return (input);
		}
		input = ft_strjoin_free_s1(input, " ");
		input = ft_strjoin_free_s1(input, next_input);
		free(next_input);
	}
	return (input);
}

/// @brief Run the shell implementations
/// @param shell
void	runnig_shell(t_shell *shell)
{
	char	*input;

	while (1)
	{
		setting_signals();
		input = readline(shell->dir_now);
		add_history(input);
		if (check_syntax(shell, input) == 0)
		{
			input = check_last_character(input);
			shell->tokens = get_tokens(shell, input);
			shell->env->var_value = make_tree(shell);
		}
		else
		{
			free (shell->env->var_value);
			shell->env->var_value = ft_itoa(2);
		}
		clean_next_round(shell);
		free(input);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_shell		*shell;

	shell = setting_shell(ac, av, envp);
	if (!shell)
		exit (ft_printf("Program closing! Could not set shell\n"));
	runnig_shell(shell);
	return (0);
}

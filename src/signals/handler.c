/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvieira <edvieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:41:27 by edvieira          #+#    #+#             */
/*   Updated: 2025/03/01 19:51:07 by edvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int signum, siginfo_t *info, void *context)
{
	(void) info;
	(void) context;
	if (signum == SIGINT)
		cntrl_c();
}

void	cntrl_c(void)
{
	if (g_sig_sign != SIGINT)
	{
		g_sig_sign = SIGINT;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

int	signals_in_child_process(t_shell *shell, int exit_code)
{
	int	signal_number;

	signal_number = WTERMSIG(exit_code);
	if (signal_number == SIGINT)
		return (ft_printf("\n"), 130);
	else if (signal_number == SIGQUIT)
	{
		(void) shell;
		ft_putstr_fd("(Core Dumped)\n", 2);
		return (131);
	}
	return (0);
}

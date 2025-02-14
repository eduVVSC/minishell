/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvieira <edvieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:41:27 by edvieira          #+#    #+#             */
/*   Updated: 2025/02/11 15:47:13 by edvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int signum, siginfo_t *info, void *context)
{
	if (signum == SIGINT)
		cntrl_c();
	if (signum == SIGQUIT)
		cntrl_backslash();
}

void	cntrl_c_heredoc(void)
{
	g_sig_sign = SIGINT;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	cntrl_c(void)
{
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	cntrl_backslash(void)
{
	rl_on_new_line();
	rl_replace_line("    ", 0);
	rl_redisplay();
}

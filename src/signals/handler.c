/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:41:27 by edvieira          #+#    #+#             */
/*   Updated: 2025/02/25 18:32:48 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signalHandler(int signum, siginfo_t *info, void *context)
{
	if (signum == SIGINT)
		cntrl_c();
	if (signum == SIGQUIT)
		cntrl_backslash();
}

void	cntrl_c(void)
{
	g_sig_sign = SIGINT;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	cntrl_backslash(void)
{
	rl_on_new_line();
	rl_replace_line("    ", 0);
	rl_redisplay();
}

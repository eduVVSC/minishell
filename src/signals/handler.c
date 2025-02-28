/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvieira <edvieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:41:27 by edvieira          #+#    #+#             */
/*   Updated: 2025/02/28 11:05:35 by edvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int signum, siginfo_t *info, void *context)
{
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

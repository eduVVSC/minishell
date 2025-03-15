/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sig_builtins.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvieira <edvieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 15:34:45 by edvieira          #+#    #+#             */
/*   Updated: 2025/03/15 15:45:46 by edvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	handeling_signals(t_shell *shell, char **envp, char **cmd)
{
	if (g_sig_sign == SIGINT || g_sig_sign == SIGQUIT)
	{
		ft_free_double_arr(&envp);
		ft_free_double_arr(&cmd);
		clean_and_terminate_with_status(shell, 130);
	}
}

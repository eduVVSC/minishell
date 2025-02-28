/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 09:16:39 by dioferre          #+#    #+#             */
/*   Updated: 2025/02/28 09:16:40 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_error(t_shell *shell)
{
	ft_putstr_fd("minishell: pipe error occured!", 2);
	clean_and_terminate_with_status(shell, -1);
}

void	fork_error(t_shell *shell)
{
	ft_putstr_fd("minishell: fork error occured!", 2);
	clean_and_terminate_with_status(shell, -1);
}

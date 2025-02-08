/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_in_parent.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:34:25 by dioferre          #+#    #+#             */
/*   Updated: 2025/02/08 17:18:06 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin_in_parent(t_shell *shell)
{
	int	original_stdin;
	int	original_stdout;
	int	exit_status;

	exit_status = 0;
	original_stdin = dup(STDIN_FILENO);
	original_stdout = dup(STDOUT_FILENO); // need to check for dup errors.
	if (has_redirection(shell->tree->content))
		handle_redirections(shell, shell->tree->content, shell->tree->last_heredoc_fd);
	exit_status = exec_builtin_especial_cases(shell, shell->tree->content);
	dup2(original_stdin, STDIN_FILENO);
	dup2(original_stdin, STDOUT_FILENO);
	close(original_stdin);
	close(original_stdout);
	return (exit_status);
}

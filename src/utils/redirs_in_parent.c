/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_in_parent.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvieira <edvieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:34:25 by dioferre          #+#    #+#             */
/*   Updated: 2025/03/01 14:30:57 by edvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parent_exit(t_shell *shell, char **cmd, int fd1, int fd2)
{
	int	exit_code;

	close(fd1);
	close(fd2);
	exit_code = get_exit_code(cmd);
	if (exit_code >= 0)
	{
		ft_free_double_arr(&cmd);
		clean_and_terminate_with_status(shell, exit_code);
	}
	if (!ft_strcmp(shell->env->var_value, "0"))
		return (1);
	return (ft_atoi(shell->env->var_value));
}

int	exec_builtin_especial_cases(t_shell *shell,
	t_tokens *node_content, int fd1, int fd2)
{
	int		exit_code;
	char	**cmd;

	exit_code = 0;
	cmd = build_cmd(&node_content);
	if (ft_strcmp(cmd[0], "cd") == 0)
		exit_code = do_cd(shell, cmd);
	else if (ft_strcmp(cmd[0], "export") == 0)
		exit_code = do_export(&shell->env, cmd);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		exit_code = do_unset(shell->env, cmd);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		exit_code = parent_exit(shell, cmd, fd1, fd2);
	ft_free_double_arr(&cmd);
	return (exit_code);
}

int	execute_builtin_in_parent(t_shell *shell)
{
	int	original_stdin;
	int	original_stdout;
	int	exit_status;

	exit_status = 0;
	original_stdin = dup(STDIN_FILENO);
	original_stdout = dup(STDOUT_FILENO);
	if (has_redirection(shell->tree->content))
		handle_redirections(shell, shell->tree->content,
			shell->tree->last_heredoc_fd);
	exit_status = exec_builtin_especial_cases(shell,
			shell->tree->content, original_stdin, original_stdout);
	dup2(original_stdin, STDIN_FILENO);
	dup2(original_stdin, STDOUT_FILENO);
	close(original_stdin);
	close(original_stdout);
	free(shell->env->var_value);
	shell->env->var_value = NULL;
	return (exit_status);
}

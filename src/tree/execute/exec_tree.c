/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 14:05:36 by dioferre          #+#    #+#             */
/*   Updated: 2025/02/10 11:05:28 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_error(void)
{
	printf("pipe error lmao!\n go fix ur code dumbass\n");
}

void	fork_error(void)
{
	printf("fork error lmao!\n go fix ur code dumbass\n");
}

int	handle_pipe(t_shell *shell, t_tree_node *node)
{
	int		fd[2];
	pid_t	pid[2];
	int		status;

 	if (pipe(fd) == -1)
		pipe_error();
	// Creating first process.
	pid[0]= fork();
	if (pid[0] == -1)
		fork_error();
	if (pid[0] == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		exec_tree(shell, node->left);
	}
	// Creating second process.
	pid[1]= fork();
	if (pid[1] == -1)
			fork_error();
	if (pid[1] == 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		exec_tree(shell, node->right);
	}
	// Cleaning up.
	close(fd[0]);
	close(fd[1]);
	waitpid(pid[0], &status, 0);
	waitpid(pid[1], &status, 0);
	clean_and_terminate_with_status(shell, WEXITSTATUS(status));
}

void	exec_tree(t_shell *shell, t_tree_node *node)
{
	if (node->content->type == PIPE)
		handle_pipe(shell, node);
	else
	{
		if (has_redirection(node->content))
			handle_redirections(shell, node->content, node->last_heredoc_fd);
		exec_cmd(shell, node->content);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 14:05:36 by dioferre          #+#    #+#             */
/*   Updated: 2025/01/05 19:24:11 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_pipe(t_shell *shell, t_tree_node *node)
{
	int		fd[2];
	pid_t	pid[2];

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
 	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
	clean_and_terminate(shell);
	clean_and_terminate(shell);
//	exit(0); // <---- Very Important!!!  Will give leaks, hopefully solved by freeing t_shell :D
}

void	handle_redirection(t_shell *shell, t_tree_node *node)
{
	if (is_heredoc_command(node->content))
		handle_heredoc_exec(shell, node);
	//else if (has_redirection)
	//	handle_redirection();
	return ;
}

// Tries to execute the given command.
void	exec_cmd(t_shell *shell, char **cmd)
{
	char	*path;
	int		i;

	if (!is_builtin(shell, cmd))
	{
		path = find_path(cmd[0], shell->env);
		// adde the transformation to 2d array of linked list
		if (!path || execve(path, cmd, NULL) == -1) // Need to translate the envp list to 2d array.
		{
			// free in here the list
			ft_putstr_fd(cmd[0], 2);
			ft_putstr_fd(" : not found\n", 2);
		}
	}
}

void	exec_tree(t_shell *shell, t_tree_node *node)
{
	if (is_pipe_node(node->content))
	{
		handle_pipe(shell, node);
	}
	else
	{
		//handle_redirection(shell, node);
		exec_cmd(shell, node->content);
		clean_and_terminate(shell);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 14:05:36 by dioferre          #+#    #+#             */
/*   Updated: 2025/01/03 18:08:29 by dioferre         ###   ########.fr       */
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
//	exit(0); // <---- Very Important!!!  Will give leaks, hopefully solved by freeing t_shell :D
}

/* void	handle_redirection()
{

} */

// Tries to execute the given command.
void	exec_cmd(t_shell *shell, char **cmd)
{
	char	*path;
	int		i;

	if (!is_builtin(shell, cmd))
	{
		path = find_path(cmd[0], shell->env);
		if (!path || execve(path, cmd, NULL) == -1)
		{
			ft_putstr_fd(cmd[0], 2);
			ft_putstr_fd(" : not found\n", 2);
		}
	}
//	exit(0);
}

void	exec_tree(t_shell *shell, t_tree_node *node)
{
	if (is_pipe_node(node->content))
	{
		handle_pipe(shell, node);
	}
	else
	{
//		handle_redirection();
		exec_cmd(shell, node->content);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 14:05:36 by dioferre          #+#    #+#             */
/*   Updated: 2024/12/29 15:05:56 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	handle_pipe(t_tree_node *node, char **envp)
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
		exec_tree(node->left, envp);
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
		exec_tree(node->right, envp);
	}
	// Cleaning up.
	close(fd[0]);
	close(fd[1]);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
	exit(0); // <---- Very Important!!!
}

/* void	handle_redirection()
{

} */

// Tries to execute the given command.
void	exec_cmd(char **cmd, char **envp)
{
	char	*path;
	int		i;

//	check_if_builtin(cmd);
	path = find_path(cmd[0], envp);
	if (!path)
	{
		printf("cmd not found!\n"); // for test purposes, will have to handle it properly later;
	}
	if (execve(path, cmd, envp) == -1)
		printf("error executing cmd!\n"); // for test purposes, will have to handle it properly later;
}

void	exec_tree(t_tree_node *node, char **envp)
{
	if (is_pipe_node(node->content))
	{
		handle_pipe(node, envp);
	}
	else
	{
//		handle_redirection();
		exec_cmd(node->content, envp);
	}
}

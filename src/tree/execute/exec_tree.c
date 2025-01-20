/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 14:05:36 by dioferre          #+#    #+#             */
/*   Updated: 2025/01/20 10:19:05 by dioferre         ###   ########.fr       */
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

/* void	handle_redirection(t_shell *shell, t_tree_node *node)
{
 	if (is_heredoc_command(node->content))
		handle_heredoc_exec2(shell, node);
	if (has_redirection(node->content)) // HEREDOCS SHOULD BE HANDLED IN HERE WITH THE REST OF THE OTHER REDIRS.
	{
		handle_normal_redir(shell, node);
		node->content = clean_redirs(node->content);
	}
	return ;
} */

// Tries to execute the given command.
void	exec_cmd(t_shell *shell, t_tokens *node_content)
{
	char	**cmd;
	char	*path;
	char	**envp;
	int		i;

	cmd = build_cmd(&node_content);
	if (!is_builtin(shell, cmd))
	{
		path = find_path(cmd[0], shell->env);
		envp = transfrom_env_to_array(shell->env);
		if (!path)
			path = ft_strdup(cmd[0]);
		printf("path = |%s|\n", path);
		print_cmds(cmd);
		if (execve(path, cmd, envp) == -1) // Need to translate the envp list to 2d array.
		{
			ft_putstr_fd(cmd[0], 2);
			ft_putstr_fd(" : not found\n", 2);
			free(path);
			ft_free_double_arr(&envp);
			ft_free_double_arr(&cmd);
		}
	}
}

void	exec_tree(t_shell *shell, t_tree_node *node)
{
	if (node->content->type == PIPE)
		handle_pipe(shell, node);
	else
	{
//		handle_redirection(shell, node);
		exec_cmd(shell, node->content);
		clean_and_terminate(shell);
	}
}

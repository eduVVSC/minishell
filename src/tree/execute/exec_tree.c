/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 14:05:36 by dioferre          #+#    #+#             */
/*   Updated: 2024/12/22 16:12:42 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	handle_pipe()
{

}

void	handle_redirection()
{

}

// Tries to execute the given command.
void	exec_cmd(char **cmd)
{
	char	*path;
	int		i;

	check_if_builtin(cmd);
	path = find_path();
	if (!path)
	{
		// free everything.
	}
	if (execve(path, cmd, envp) == -1)
		display_error();
}

void	exec_tree(t_tree_node *node)
{
	if (is_pipe(node->content))
	{
		handle_pipe();
	}
	else
	{
		handle_redirection();
		exec_cmd();
	}
}

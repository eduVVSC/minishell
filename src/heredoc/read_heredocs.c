/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_heredocs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvieira <edvieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 15:55:30 by dioferre          #+#    #+#             */
/*   Updated: 2025/02/11 15:31:08 by edvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_heredocs(t_shell *shell, t_tree_node *node)
{
	int			fd[2];
	int			nr_of_heredocs;
	t_tokens	*current;

	current = node->content;
	nr_of_heredocs = count_heredocs(current);
	if (!nr_of_heredocs)
		return ;
	if (pipe(fd) == -1)
		pipe_error();
	while (current)
	{
		if (current->type == HEREDOC)
		{
			handle_heredoc(shell, current, fd[WRITE]);
			if (nr_of_heredocs > 1)
			{
				nr_of_heredocs--;
				close_fds(fd);
				if (pipe(fd) == -1)
					pipe_error();
			}
			else
				close(fd[WRITE]);
		}
		if (g_sig_sign == SIGINT)
		{
			close_fds(fd);
			return ;
		}
		current = current->next;
	}
	node->last_heredoc_fd = fd[READ];
}

void	check_for_heredocs(t_shell *shell, t_tree_node *node)
{
	if (!node || g_sig_sign == SIGINT)
		return ;
	if (node->content->type == PIPE && g_sig_sign != SIGINT)
	{
		check_for_heredocs(shell, node->left);
		check_for_heredocs(shell, node->right);
	}
	else if (g_sig_sign != SIGINT)
		read_heredocs(shell, node);
}

void	process_heredocs(t_shell *shell)
{
	int		exit_status;

	check_for_heredocs(shell, shell->tree);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_heredocs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 15:55:30 by dioferre          #+#    #+#             */
/*   Updated: 2025/02/28 09:11:56 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	read_heredoc_on_loop(t_shell *s, t_tokens *curr, int *fd, int nr_heredocs)
{
	while (curr)
	{
		if (curr->type == HEREDOC)
		{
			handle_heredoc(s, curr, fd[WRITE]);
			if (nr_heredocs > 1)
			{
				nr_heredocs--;
				close_fds(fd);
				if (pipe(fd) == -1)
					pipe_error(s);
			}
			else
				close(fd[WRITE]);
		}
		if (g_sig_sign == SIGINT)
		{
			close_fds(fd);
			return (-1);
		}
		curr = curr->next;
	}
	return (fd[READ]);
}

void	read_heredocs(t_shell *shell, t_tree_node *node)
{
	int			fd[2];
	int			nr_of_heredocs;
	int			last_fd;
	t_tokens	*current;

	current = node->content;
	nr_of_heredocs = count_heredocs(current);
	if (!nr_of_heredocs)
		return ;
	if (pipe(fd) == -1)
		pipe_error(shell);
	last_fd = read_heredoc_on_loop(shell, current, fd, nr_of_heredocs);
	if (last_fd == -1)
		return ;
	node->last_heredoc_fd = last_fd;
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_heredocs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 15:55:30 by dioferre          #+#    #+#             */
/*   Updated: 2025/02/08 17:44:00 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_there_a_heredoc_in_node(t_tree_node *node)
{
	if (!node)
		return (FALSE);
	while (node->content)
	{
		if (node->content->type == HEREDOC)
			return (TRUE);
		node->content = node->content->next;
	}
	return (FALSE);
}

void	read_heredocs(t_shell *shell, t_tree_node *node)
{
	int	fd[2];
	int	nr_of_heredocs;
	t_tokens	*tmp;

	tmp = node->content;
	nr_of_heredocs = count_heredocs(tmp);
 	if (pipe(fd) == -1)
		pipe_error();
	while (nr_of_heredocs)
	{
		if (tmp->type == HEREDOC)
		{
			handle_heredoc(shell, tmp, fd[WRITE]);
			nr_of_heredocs--;
		}
		if (sig_sign == SIGINT)
		{
			close_fds(fd);
			clean_and_terminate_with_status(shell, 130);
		}
		tmp = tmp->next;
	}
	close (fd[WRITE]);
	node->last_heredoc_fd = fd[READ];
}

void	check_for_heredocs(t_shell *shell, t_tree_node *node)
{
	if (is_there_a_heredoc_in_node(node->left) && sig_sign != SIGINT)
		read_heredocs(shell, node->left);
	if (node->right && sig_sign != SIGINT)
		check_for_heredocs(shell, node->right);
	else if(sig_sign != SIGINT)
		read_heredocs(shell, node);
	return ;
}

void	process_heredocs(t_shell *shell)
{
	int		exit_status;

	check_for_heredocs(shell, shell->tree);
	if (sig_sign)
	{
		//lol deu merda hahahahahhahahah
	}
}

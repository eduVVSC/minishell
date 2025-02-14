/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvieira <edvieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 10:55:04 by dioferre          #+#    #+#             */
/*   Updated: 2025/02/11 15:22:11 by edvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Create a heredoc node with
/// @brief everything set to NULL and the key given by read
/// @param key
/// @return (NULL -> malloc error) (node -> success)
t_heredock	*create_heredoc_node(t_tokens *key)
{
	t_heredock	*heredock;

	heredock = malloc(sizeof(t_heredock));
	if (!heredock)
		return (NULL);
	if (!key)
		heredock->key = NULL;
	else
		heredock->key = ft_strdup(key->token);
	heredock->state = key->state;
	heredock->fullinput_until_key = NULL;
	heredock->next = NULL;
	return (heredock);
}

/// @brief Will create the heredoc node and execute it
/// @param shell
/// @param redir
void	handle_heredoc(t_shell *shell, t_tokens *redir, int fd)
{
	t_heredock	*heredock;

	heredock = create_heredoc_node(redir->next);
	if (heredock)
		doing_heredock(shell, heredock, fd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 10:55:04 by dioferre          #+#    #+#             */
/*   Updated: 2025/01/31 11:05:06 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Create a heredoc node with everything set to NULL and the key given by read
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

/// @brief
/// @param shell
/// @param redir
/// @return
int	handle_heredoc(t_shell *shell, t_tokens *redir)
{
	t_heredock	*heredock;

	heredock = create_heredoc_node(redir->next);
	if (!heredock)
		return (-1);
	return (doing_heredock(shell, heredock));
}

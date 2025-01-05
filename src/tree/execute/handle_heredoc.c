/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 17:55:19 by dioferre          #+#    #+#             */
/*   Updated: 2025/01/05 19:24:10 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_heredoc_node(t_heredock *node)
{
	free(node->key);
	if (node->fullinput_until_key)
		free(node->fullinput_until_key);
	free(node);
}

t_heredock	*create_heredoc_node(t_heredock *node, char *key)
{
	node->key = ft_strdup(key);
	node->fullinput_until_key = NULL;
	node->next = NULL;
	free(key);
	return (node);
}

// Checks if the given command has a heredoc as an argument.
int	is_heredoc_command(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != NULL)
	{
		if (!ft_strcmp(cmd[i], "<<"))
			return (1);
		i++;
	}
	return(0);
}

int	handle_heredoc_exec(t_shell *shell, t_tree_node *node)
{
	t_heredock	*tmp;
	int			i;

	i = 0;
	while (node->content[i] != NULL)
	{
		if (!ft_strcmp(node->content[i], "<<"))
		{
			i++;
			if (!shell->heredock) // first heredock (head)
			{
				shell->heredock = malloc(sizeof(t_heredock));
				if (!shell->heredock)
					return (-1);
				else if (node->content[i] && (node->content[i][0] != '<' && node->content[i][0] != '>'))
				{
					create_heredoc_node(shell->heredock, node->content[++i]);
					tmp = shell->heredock;
				}
				else
					return (-1); // heredoc error of not having any
			}
			/* else
			{
				if (node->content[i] && (node->content[i][0] != '<' && node->content[i][0] != '>'))
				{
					tmp->next create_heredoc_node()
				}
				else
					return (-1);
			} */
			break; // should keep iterating until it finds the last heredoc, but we'll leave it like this for now.
		}
		i++;
	}
	shell->heredock->next = NULL;
	shell->heredock = doing_heredock(shell->heredock);
	printf("%s"	, shell->heredock->fullinput_until_key);
	// put the resolting string in the fd = 1
	return (0);
}

int	handle_heredoc_exec2(t_shell *shell, t_tree_node *node)
{
	int	i;

	i = 0;
	while (node->content[i] != NULL)
	{
		if (!ft_strcmp(node->content[i], "<<"))
		{
			shell->heredock = malloc(sizeof(t_heredock));
			if (!shell->heredock)
				return (-1);
			shell->heredock->key = ft_strdup(node->content[++i]);
			break; // should keep iterating until it finds the last heredoc, but we'll leave it like this for now.
		}
		i++;
	}
	shell->heredock->next = NULL;
	shell->heredock = doing_heredock(shell->heredock);
	printf("%s"	, shell->heredock->fullinput_until_key);
	// put the resolting string in the fd = 1
	return (0);
}

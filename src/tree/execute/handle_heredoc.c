/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 17:55:19 by dioferre          #+#    #+#             */
/*   Updated: 2025/01/07 17:15:32 by dioferre         ###   ########.fr       */
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

t_heredock	*create_heredoc_node(char *key)
{
	t_heredock	*node;

	node = malloc(sizeof(t_heredock));
	if (!node)
		return (NULL);
	if (!key)
		node->key = NULL;
	else
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

int	many_to_alloc(char **heredoc_cmd)
{
	int	to_alloc;
	int	i;

	i = 0;
	to_alloc = 0;
	while (heredoc_cmd[i])
	{
		if (ft_strcmp(heredoc_cmd[i], "<<") == 0)
			i++;
		else
			to_alloc++;
		if (heredoc_cmd[i])
			i++;
	}
	return (to_alloc);
}

char	**takeof_heredoc_from_cmd(t_tree_node *node)
{
	char	**rewriten_node;
	int		i;
	int		j;
	int		to_alloc;

	j = -1;
	i = -1;
	to_alloc = many_to_alloc(node->content);
	rewriten_node = malloc(sizeof(char **) * (to_alloc + 1));
	if (!rewriten_node)
		return (NULL);
	while (node->content[++i] && j < (to_alloc - 1))
	{
		if (ft_strcmp(node->content[i], "<<") == 0)
			i++;
		else
		{
			if (!node->content)
				rewriten_node = NULL;
			else
				rewriten_node[++j] = ft_strdup(node->content[i]);
		}
	}
	rewriten_node[++j] = NULL;
	return (rewriten_node);
}

// NEED TO HANDLE THE "CAT <<", the heredoc key in the node needs to be null, in order to the funtion which will execute the heredoc
// see it at its time, and exit the error need, but it should execute the other heredocs before it


// quando for fazer o take_off quotes tem de deixar junto oque estava dentro da quote -> "ola como" -> (ola como)
// command execution need to break, when return any num different than (0)
int	handle_heredoc_exec(t_shell *shell, t_tree_node *node)
{
	t_heredock	*tmp;
	int			i;

	i = 0;
	while (node->content[i] != NULL)
	{
		if (ft_strcmp(node->content[i], "<<") == 0)
		{
			if(ft_strcmp(node->content[++i], "<<") == 0)
			{
				i = -1;
				break ;
			}
			if (!shell->heredock)
			{
				shell->heredock = create_heredoc_node(node->content[i]);
				tmp = shell->heredock;
			}
			else
			{
				tmp->next = create_heredoc_node(node->content[i]);
				tmp = tmp->next;
			}
		}
		i++;
	}
	if (i == -1)
		return (printf("bash: syntax error near unexpected token `<<'\n"), 1);
	node->content = takeof_heredoc_from_cmd(node);
//	printf("Command after heredoc: ");
//	print_cmds(node->content);
	return (doing_heredock(shell->heredock));
}

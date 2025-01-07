/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 13:18:17 by dioferre          #+#    #+#             */
/*   Updated: 2025/01/07 17:53:01 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Counts the number of commands in the list.
int	count_nodes(t_tokens *tokens)
{
	int	nodes;

	nodes = 1;
	if (!tokens)
		return (0);
	while (tokens)
	{
		if (tokens->type == PIPE)
		{
			nodes++;
			if (tokens->next)
				nodes++;
		}
		if (!tokens->next)
			break;
		tokens = tokens->next;
	}
	return (nodes);
}

// Creates an enpty t_cmds node
static t_cmds	*make_node(void)
{
	t_cmds	*node;

	node = malloc(sizeof(t_cmds));
	if (!node)
		return (NULL);
	node->cmd = NULL;
	node->next = NULL;
	return (node);
}

void	make_nodes(t_cmds *head, int nr_of_nodes)
{
	t_cmds	*tmp;
	int	i;

	tmp = head;
	i = 0;
	while (i < nr_of_nodes - 1) // creates a new node and links it to the current one.
	{
		tmp->next = make_node();
		tmp = tmp->next;
		i++;
	}
}

// Builds a linked list of commands for the sake of organization.
t_cmds	*build_cmd_list(t_tokens *tokens)
{
	t_cmds *cmd_list;
	t_cmds *head;
	int	i;
	int	nr_of_nodes;

	i = 0;
	nr_of_nodes = count_nodes(tokens);
	head = make_node();
	cmd_list = head;
	make_nodes(head, nr_of_nodes);
	while (i < nr_of_nodes)
	{
		cmd_list->cmd = build_cmd(&tokens);
		cmd_list = cmd_list->next;
		i++;
	}
	return(head);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 13:18:17 by dioferre          #+#    #+#             */
/*   Updated: 2024/12/10 10:30:39 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
t_cmds	*build_cmd_list(char **cmds)
{
	t_cmds *cmd_list;
	t_cmds *head;
	int	i;
	int	nr_of_nodes;
	char	**str;

	nr_of_nodes = 0;
	while (cmds[nr_of_nodes])
		nr_of_nodes++;
	i = 0;
	head = make_node();
	cmd_list = head;
	make_nodes(head, nr_of_nodes);
	while (cmds[i])
	{
		cmd_list->cmd = ft_split(cmds[i], ' ');
		cmd_list = cmd_list->next;
//		cmd_list->cmd[0] = ft_strjoin("/bin/", cmd_list->cmd[0]);
		i++;
	}
	ft_free_double_arr(&cmds);
	return(head);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 13:18:17 by dioferre          #+#    #+#             */
/*   Updated: 2025/02/28 11:14:10 by dioferre         ###   ########.fr       */
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
	node->token_list = NULL;
	node->next = NULL;
	return (node);
}

void	make_nodes(t_cmds *head, int nr_of_nodes)
{
	t_cmds	*tmp;
	int		i;

	tmp = head;
	i = 0;
	while (i < nr_of_nodes - 1)
	{
		tmp->next = make_node();
		tmp = tmp->next;
		i++;
	}
}

/// @brief Creates a new cmd and fills it with the current token.
/// @param token
/// @return (new_cmd_head)
static t_cmds	*make_head(t_tokens **token)
{
	t_cmds	*head;

	head = malloc(sizeof(t_cmds));
	if (!head)
		return (NULL);
	head->token_list = copy_token_node(*token);
	head->next = NULL;
	(*token) = (*token)->next;
	return (head);
}

static void	handle_pipe_case(t_cmds **cmd, t_tokens **tokens)
{
	t_cmds	*pipe_node;
	t_cmds	*next_head;

	pipe_node = make_head(tokens);
	next_head = make_head(tokens);
	(*cmd)->next = pipe_node;
	pipe_node->next = next_head;
	(*cmd) = next_head;
}

// Builds a linked list of commands for the sake of organization.
t_cmds	*build_cmd_list(t_tokens *tokens)
{
	t_cmds		*cmd;
	t_cmds		*head;

	head = make_head(&tokens);
	cmd = head;
	while (tokens)
	{
		if (tokens->type == PIPE)
			handle_pipe_case(&cmd, &tokens);
		if (tokens && tokens->type != PIPE)
		{
			ft_lstadd_back_a(&cmd->token_list, copy_token_node(tokens));
			tokens = tokens->next;
		}
	}
	return (head);
}

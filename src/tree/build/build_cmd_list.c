/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 13:18:17 by dioferre          #+#    #+#             */
/*   Updated: 2025/02/04 12:07:51 by dioferre         ###   ########.fr       */
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

t_tokens	*copy_token_node(t_tokens *token)
{
	t_tokens	*tmp;

	tmp = malloc(sizeof(t_tokens));
	if (!tmp)
		return (NULL);
	tmp->type = token->type;
	tmp->index = token->index;
	tmp->state = token->state;
	tmp->token = ft_strdup(token->token);
	tmp->next = NULL;
	return (tmp);
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
void print_this_shit(t_cmds *cmds)
{
	while (cmds)
	{
		print_tokens(cmds->token_list);
		cmds = cmds->next;
	}
}


t_tokens	*ft_lstlast_a(t_tokens *lst)
{
	t_tokens	*temp;

	if (!lst)
		return (NULL);
	temp = lst;
	while ((temp->next) != NULL)
		temp = temp->next;
	return (temp);
}


void	ft_lstadd_back_a(t_tokens **lst, t_tokens *new)
{
	t_tokens	*end;

	end = ft_lstlast_a(*lst);
	if (end == NULL)
	{
		*lst = new;
		return ;
	}
	end->next = new;
}
// Builds a linked list of commands for the sake of organization.
t_cmds	*build_cmd_list(t_tokens *tokens)
{
	t_cmds		*cmd;
	t_cmds		*head;
	t_tokens	*tmp;

	head = make_head(&tokens);
	cmd = head;
	// criou a head
	while (tokens)  //populate node (head included )
	{
		if (tokens->type == PIPE)
			handle_pipe_case(&cmd, &tokens);
		if (tokens && tokens->type != 7) // its bad somehow
			ft_lstadd_back_a(&cmd->token_list ,copy_token_node(tokens));
		if (tokens)
			tokens = tokens->next;
	}
//	print_this_shit(head);
	return(head);
}


/* // Builds a linked list of commands for the sake of organization.
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
} */

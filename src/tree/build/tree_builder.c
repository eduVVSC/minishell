/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_builder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:35:26 by dioferre          #+#    #+#             */
/*   Updated: 2025/01/07 17:53:29 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Checks the content of a cmd_list for pipes.
int	is_pipe_node(char **content)
{
	if (content[0][0] == '|')
		return (1);
	return (0);
}

// Initializes a tree node with everything set to NULL;
t_tree_node	*init_tree_node(void)
{
	t_tree_node	*new_node;

	new_node = malloc(sizeof(t_tree_node));
	new_node->content = NULL;
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}

void	build_tree(t_tree_node *top_node, t_cmds *cmd_list)
{
	t_tree_node	*right;
	t_tree_node	*left;

	right = init_tree_node();
	left = init_tree_node();
	if (cmd_list->next) // Checks if there is only one command.
	{
		if (cmd_list->next->next) // Checks if there is something after the pipe.
		{
			top_node->content = cmd_list->next->cmd;
			left->content = cmd_list->cmd;
			right->content = cmd_list->next->next->cmd;
			cmd_list = cmd_list->next->next;
			top_node->right = right;
			top_node->left = left;
			if (cmd_list->next)
				build_tree(right, cmd_list);
		}
		// NOTHING WAS FOUND AFTER THE PIPE - TO DO:    ELSE -> OPEN HEREDOC!!!!
	}
	else
	{
		top_node->content = cmd_list->cmd;
		free(left);
		free(right);
	}
}

void	print_tree(t_tree_node *head)
{
	int	layer;

	layer = 1;
	if (!head->right)
	{
		printf("Layer: %d\n", layer);
		printf("Node: ");
		print_cmds(head->content);
		if (head->left)
		{
			printf("Left: ");
			print_cmds(head->left->content);
		}
		printf("---------------------\n\n");
	}
	while(head->right)
	{
		printf("Layer: %d\n", layer);
		printf("Node: ");
		print_cmds(head->content);
		if (head->left)
		{
			printf("Left: ");
			print_cmds(head->left->content);
		}
		if (head->right)
		{
			printf("Right: ");
			print_cmds(head->right->content);
		}
		head = head->right;
		printf("---------------------\n\n");
		layer++;
	}
}

// checks if the input given is one of the special cases where it should be executed on the parent process.
int	is_builtin_special_case(t_cmds *cmd_list)
{
	char	*first_cmd;

	first_cmd = cmd_list->cmd[0]; // pointer to first command.
	if (cmd_list->next == NULL)
	{
		if (!ft_strcmp(first_cmd, "unset") ||
			!ft_strcmp(first_cmd, "export") ||
			!ft_strcmp(first_cmd, "cd"))
			return (1);
	}
	return (0);
}

void	make_tree(t_shell *shell)
{
	pid_t		pid;
	int			i;

	i = 0;
	shell->tree = init_tree_node();
//	print_tokens(shell->tokens);
	shell->cmd_list = build_cmd_list(shell->tokens);
//	print_cmds(shell->cmd_list->cmd);
	build_tree(shell->tree, shell->cmd_list);
//	print_tree(shell->tree);
 	if (is_builtin_special_case(shell->cmd_list)) // checks if its one of the special cases where it should be executed on parent process.
		exec_cmd(shell, shell->cmd_list->cmd);
	else // if not executes a fork and creates a child process.
	{
		pid = fork();
		if (pid == 0)
			exec_tree(shell, shell->tree);
		waitpid(pid, NULL, 0);
 		if (pid == 0)
			clean_and_terminate(shell);
	}
}

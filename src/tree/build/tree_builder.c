/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_builder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:35:26 by dioferre          #+#    #+#             */
/*   Updated: 2025/02/25 11:02:59 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Initializes a tree node with everything set to NULL;
t_tree_node	*init_tree_node(void)
{
	t_tree_node	*new_node;

	new_node = malloc(sizeof(t_tree_node));
	new_node->content = NULL;
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->last_heredoc_fd = -7;
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
		top_node->content = cmd_list->next->token_list; // ADD PIPE ON TOKENIZATION
		left->content = cmd_list->token_list;
		right->content = cmd_list->next->next->token_list;
		cmd_list = cmd_list->next->next;
		top_node->right = right;
		top_node->left = left;
		if (cmd_list->next)
			build_tree(right, cmd_list);
	}
	else
	{
		top_node->content = cmd_list->token_list;
		free(left);
		free(right);
	}
}

void	print_tree_tokens(t_tokens *tokens)
{
	while (tokens)
	{
		printf("(%s) ",tokens->token);
		tokens = tokens->next;
	}
	printf("\n");
}

void	print_tree(t_tree_node *head)
{
	int	layer;

	layer = 1;
	if (!head->right)
	{
		printf("Layer: %d\n", layer);
		printf("Node: ");
		print_tree_tokens(head->content);
		if (head->left)
		{
			printf("Left: ");
			print_tree_tokens(head->left->content);
		}
		printf("---------------------\n\n");
	}
	while(head->right)
	{
		printf("Layer: %d\n", layer);
		printf("Node: ");
		print_tree_tokens(head->content);
		if (head->left)
		{
			printf("Left: ");
			print_tree_tokens(head->left->content);
		}
		if (head->right)
		{
			printf("Right: ");
			print_tree_tokens(head->right->content);
		}
		head = head->right;
		printf("---------------------\n\n");
		layer++;
	}
}

// checks if the input given is one of the special cases where it should be executed on the parent process.
int	is_builtin_special_case(t_cmds *first_cmd)
{
	char	*first_input;

	first_input = first_cmd->token_list->token; // pointer to first command.
	if (first_cmd->next == NULL)
	{
		if (!ft_strcmp(first_input, "unset") ||
			!ft_strcmp(first_input, "export") ||
			!ft_strcmp(first_input, "cd") ||
			!ft_strcmp(first_input, "exit"))
			return (1);
	}
	return (0);
}

char	*make_tree(t_shell *shell)
{
	pid_t		pid;
	int			exit_code;

	shell->tree = init_tree_node();
	shell->cmd_list = build_cmd_list(shell->tokens);
	build_tree(shell->tree, shell->cmd_list);
	signal(SIGINT, cntrl_c_heredoc);
	process_heredocs(shell); // cat << a |
	if (g_sig_sign == SIGINT)
		return (clean_fds(shell->tree), free(shell->env->var_value), ft_itoa(WEXITSTATUS(130)));
	if (is_builtin_special_case(shell->cmd_list)) // checks if its one of the special cases where it should be executed on parent process.
	{
		free(shell->env->var_value);
		shell->env->var_value = NULL;
		return (ft_itoa(execute_builtin_in_parent(shell)));
	}
	else // if not executes a fork and creates a child process.
	{
		pid = fork();
		if (pid == 0)
			exec_tree(shell, shell->tree);
		waitpid(pid, &exit_code, 0);
		if (pid == 0)
			clean_and_terminate(shell);
		clean_fds(shell->tree);
		free(shell->env->var_value);
		return (ft_itoa(WEXITSTATUS(exit_code)));
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_builder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvieira <edvieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:35:26 by dioferre          #+#    #+#             */
/*   Updated: 2025/02/28 14:00:05 by edvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Initializes a tree node with everything set to NULL;
t_tree_node	*init_tree_node(void)
{
	t_tree_node	*new_node;

	new_node = malloc(sizeof(t_tree_node));
	if (!new_node)
		return (NULL);
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
	if (cmd_list->next)
	{
		top_node->content = cmd_list->next->token_list;
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

// checks if the input given is one of the
// special cases where it should be executed on the parent process.
int	is_builtin_special_case(t_cmds *first_cmd)
{
	char	*first_input;

	first_input = first_cmd->token_list->token;
	if (first_cmd->next == NULL)
	{
		if (!ft_strcmp(first_input, "unset")
			|| !ft_strcmp(first_input, "export")
			|| !ft_strcmp(first_input, "cd")
			|| !ft_strcmp(first_input, "exit"))
			return (1);
	}
	return (0);
}

char	*tree_exec(t_shell *shell, pid_t pid)
{
	int	exit_code;

	exit_code = 0;
	if (is_builtin_special_case(shell->cmd_list))
		return (ft_itoa(execute_builtin_in_parent(shell)));
	else
	{
		pid = fork();
		if (pid == 0)
		{
			signal(SIGINT, SIG_IGN);
			exec_tree(shell, shell->tree);
		}
		waitpid(pid, &exit_code, 0);
		if (pid == 0)
			clean_and_terminate(shell);
		clean_fds(shell->tree);
		free(shell->env->var_value);
		return (ft_itoa(WEXITSTATUS(exit_code)));
	}
}

char	*make_tree(t_shell *shell)
{
	pid_t		pid;
	int			exit_code;

	shell->tree = init_tree_node();
	shell->cmd_list = build_cmd_list(shell->tokens);
	build_tree(shell->tree, shell->cmd_list);
	process_heredocs(shell);
	if (g_sig_sign == SIGINT)
		return (clean_fds(shell->tree),
			free(shell->env->var_value), ft_strdup("130"));
	return (tree_exec(shell, pid));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 17:50:12 by edvieira          #+#    #+#             */
/*   Updated: 2025/02/11 11:58:28 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Free the env list and each one of the nodes and set env to NULL
/// @param env
void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free_env_node(tmp);
	}
	env = NULL;
}

/// @brief Free all the node memory and set them to NULL
/// @param node
void	free_env_node(t_env *node)
{
	if (node->var_name)
		free(node->var_name);
	if (node->operant)
		free(node->operant);
	if (node->var_value)
		free(node->var_value);
	node->var_name = NULL;
	node->operant = NULL;
	node->var_value = NULL;
	free(node);
	node = NULL;
}

/// @brief Clean the tokens and set the list to NULL at the end
/// @param tokens
void	free_tokens(t_tokens *tokens)
{
	t_tokens	*tmp;

	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
	//	if (tmp->type == 7)
		free(tmp->token);
		free(tmp);
	}
	tokens = NULL;
}

/// @brief Free the command list and it's nodes itens, set the list to NULL at the end
/// @param cmd
void	free_cmd(t_cmds *cmd)
{
	t_cmds	*tmp;

	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
//		ft_free_double_arr(&tmp->cmd);
		free(tmp);
	}
	cmd = NULL;
}


/// @brief Clean the Shell and exits with given exit code
/// @param shell
/// @return (0)
int	clean_and_terminate_with_status(t_shell *shell, int exit_code)
{
	clean_fds(shell->tree);
	free_tree(shell->tree);
	free_tokens(shell->tokens);
	free_cmd_list(shell->cmd_list);
	free_env(shell->env);
	free(shell->dir_now);
	free(shell);
	exit(exit_code);
}



/// @brief Clean the Shell and exits
/// @param shell
/// @return (0)
int	clean_and_terminate(t_shell *shell)
{
	free_tree(shell->tree);
	free_tokens(shell->tokens);
	free_cmd_list(shell->cmd_list);
	free_env(shell->env);
	free(shell->dir_now);
	free(shell);
	exit(0);
}

/// @brief Clean the Shell and returns
/// @param shell
/// @return (0)
int	clean_all_and_close(t_shell *shell)
{
	free_tree(shell->tree);
	free_tokens(shell->tokens);
	free_cmd_list(shell->cmd_list);
	free_env(shell->env);
	free(shell->dir_now);
	free(shell);
	return (0);
}

void	clean_fds(t_tree_node *node)
{
	if (!node)
		return;
	if (node->content->type == PIPE)
	{
		clean_fds(node->left);
		clean_fds(node->right);
	}
	else if (node->last_heredoc_fd >= 0)
		close(node->last_heredoc_fd);
}

/// @brief Clean the used variable trought one input(tree, tokens and cmd_list) and set them to NULL
/// @param shell
void	clean_next_round(t_shell *shell)
{
	free_tree(shell->tree);
	free_tokens(shell->tokens);
	free_cmd_list(shell->cmd_list);
	shell->tree = NULL;
	shell->tokens = NULL;
	shell->cmd_list = NULL;
	g_sig_sign = 0;
}

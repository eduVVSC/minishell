/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvieira <edvieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 17:50:12 by edvieira          #+#    #+#             */
/*   Updated: 2025/02/11 15:49:39 by edvieira         ###   ########.fr       */
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
		free(tmp->token);
		free(tmp);
	}
	tokens = NULL;
}

/// @brief Free the command list and it's nodes
/// @brief  itens, set the list to NULL at the end
/// @param cmd
void	free_cmd(t_cmds *cmd)
{
	t_cmds	*tmp;

	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		free(tmp);
	}
	cmd = NULL;
}

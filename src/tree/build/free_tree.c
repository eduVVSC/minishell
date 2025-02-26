/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvieira <edvieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 16:31:21 by dioferre          #+#    #+#             */
/*   Updated: 2025/02/26 14:45:54 by edvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token_list(t_tokens *tokens)
{
	if (tokens == NULL)
		return ;
	free_token_list(tokens->next);
	free(tokens->token);
	free(tokens);
	tokens = NULL;
}

void	free_tree(t_tree_node *head)
{
	if (head == NULL)
		return ;
	free_tree(head->left);
	free_tree(head->right);
	free(head);
}

void	free_cmd_list(t_cmds *cmds)
{
	if (cmds == NULL)
		return ;
	free_cmd_list(cmds->next);
	free_token_list(cmds->token_list);
	free(cmds);
	cmds = NULL;
}

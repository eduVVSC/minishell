/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 16:31:21 by dioferre          #+#    #+#             */
/*   Updated: 2025/01/20 10:18:03 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tree(t_tree_node *head)
{
	if (head == NULL)
		return;

	free_tree(head->left);
	free_tree(head->right);
	// free token list lol;
	free(head);
}

void	free_cmd_list(t_cmds *cmds)
{
	if (cmds == NULL)
		return;
	free_cmd_list(cmds->next);
	free(cmds);
	cmds = NULL;
}

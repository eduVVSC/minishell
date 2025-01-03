/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 16:31:21 by dioferre          #+#    #+#             */
/*   Updated: 2025/01/03 16:23:44 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	free_tree(t_tree_node *head)
{
	if (head == NULL)
		return;

	free_tree(head->left);
	free_tree(head->right);
	ft_free_double_arr(&head->content);
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

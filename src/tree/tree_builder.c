/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_builder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:35:26 by dioferre          #+#    #+#             */
/*   Updated: 2024/11/29 14:21:25 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
 t_tree_node	*build_tree(t_tokens *tokens)
{
	t_tree_node	*tree;
	char		*cmds;
	int			i;

	i = 0;
	tree = malloc(sizeof(t_tree_node));
	cmds = build_cmds(tokens);
	while (cmds)
	{
		tree->content = (cmds[i]);
		if (cmds[i + 1])
		{
			i += 1;
			tree->left->content = (cmds[i]);
		}
	}
} */

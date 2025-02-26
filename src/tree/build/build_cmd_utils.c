/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvieira <edvieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:42:56 by edvieira          #+#    #+#             */
/*   Updated: 2025/02/26 14:43:24 by edvieira         ###   ########.fr       */
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvieira <edvieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:42:56 by edvieira          #+#    #+#             */
/*   Updated: 2025/02/26 16:14:29 by edvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens	*copy_token_node(t_tokens *token)
{
	t_tokens	*tmp;

	tmp = malloc(sizeof(t_tokens));
	if (!tmp)
		return (NULL);
	tmp->type = token->type;
	tmp->index = token->index;
	tmp->state = token->state;
	tmp->token = ft_strdup(token->token);
	tmp->next = NULL;
	return (tmp);
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

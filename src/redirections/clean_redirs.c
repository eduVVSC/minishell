/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_redirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 18:03:47 by dioferre          #+#    #+#             */
/*   Updated: 2025/02/28 11:14:44 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token(t_tokens *token)
{
	free(token->token);
	token->token = NULL;
	token->next = NULL;
	token->state = 0;
	token->type = 0;
}

int	is_redir_token(t_tokens *tokens)
{
	if ((tokens->type == INFILE
			|| tokens->type == APP_OUTFILE
			|| tokens->type == TRU_OUTFILE
			|| tokens->type == HEREDOC)
		&& tokens->state == GENERAL)
		return (1);
	return (0);
}

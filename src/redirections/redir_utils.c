/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvieira <edvieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 15:04:23 by dioferre          #+#    #+#             */
/*   Updated: 2025/03/01 17:10:06 by edvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup_from_input(int fd)
{
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	dup_to_output(int fd)
{
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

int	check_for_cmds(t_tokens *tokens)
{
	while (tokens)
	{
		if (tokens->type == HEREDOC
			|| tokens->type == TRU_OUTFILE
			|| tokens->type == APP_OUTFILE
			|| tokens->type == INFILE)
		{
			if (tokens->next)
			{
				tokens = tokens->next;
				if (tokens->next)
					tokens = tokens->next;
				else
					return (-1);
			}
			else
				return (-1);
		}
		else
			return (1);
	}
	return (-1);
}

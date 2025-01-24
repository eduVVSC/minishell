/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 13:17:15 by dioferre          #+#    #+#             */
/*   Updated: 2025/01/20 13:05:21 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_redir(t_tokens *tokens)
{
	if ((tokens->type == INFILE
		|| tokens->type == APP_OUTFILE
		|| tokens->type == TRU_OUTFILE)
		&& tokens->state == GENERAL)
			return (1);
	return (0);
}

int	count_args(t_tokens *tokens)
{
	int	args;

	args = 0;
	if (!tokens)
		return (0);
	while(tokens)
	{
		if (is_redir(tokens))
		{
			tokens = tokens->next->next;
			continue;
		}
		else if (tokens->type == HEREDOC && tokens->state == GENERAL)
		{
			tokens = tokens->next;
			continue;
		}
		else if (tokens->type != SPACE)
			args++;
		if (!tokens->next)
			break;
		tokens = tokens->next;
	}
	return (args);
}

char	**build_cmd(t_tokens **tokens)
{
	char	**cmd;
	int		nr_args;
	int		i;

	i = 0;
	nr_args = count_args((*tokens));
	cmd = malloc((nr_args + 1) * sizeof(char *));
	while(i < nr_args && (*tokens))
	{
		if ((*tokens)->type == SPACE
			|| ((*tokens)->type == HEREDOC && (*tokens)->state == GENERAL))
			(*tokens) = (*tokens)->next;
		else if (is_redir(*tokens))
			(*tokens) = (*tokens)->next->next;
		else
		{
			cmd[i] = ft_strdup((*tokens)->token);
			(*tokens) = (*tokens)->next;
			i++;
		}
	}
	cmd[i] = 0;
	return (cmd);
}


void	print_cmds(char **cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
	{
		printf("(%s) ",cmds[i]);
		i++;
	}
	printf("\n");
}

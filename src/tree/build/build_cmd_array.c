/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 13:17:15 by dioferre          #+#    #+#             */
/*   Updated: 2025/01/20 10:09:29 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_args(t_tokens *tokens)
{
	int	args;

	args = 1;
	if (!tokens)
		return (0);
	while(tokens)
	{
		if (tokens->type != 7)
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
		if ((*tokens)->type == 7)
		{
			(*tokens) = (*tokens)->next;
			continue;
		}
		cmd[i] = (*tokens)->token;
		(*tokens) = (*tokens)->next;
		i++;
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

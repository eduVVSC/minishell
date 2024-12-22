/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 13:17:15 by dioferre          #+#    #+#             */
/*   Updated: 2024/12/10 10:03:36 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Counts the number of commands in the list.
int	count_cmds(t_tokens *tokens)
{
	int	i;

	i = 1;
	if (!tokens)
		return (0);
	while (tokens)
	{
		if (tokens->type == 1)
		{
			if (tokens->next)
				i++;
			i++;
		}
		if (!tokens->next)
			break;
		tokens = tokens->next;
	}
	return (i);
}

// Joins two strings and replaces the content of s1
// with the result of strjoin
void	strjoin_and_replace(char **s1, char *s2)
{
	char *tmp;

	tmp = ft_strdup(*s1);
	free (*s1);
	*s1 = ft_strjoin(tmp, s2);
	free (tmp);
}

/* Builds a command based on the token list
and the given index of the command on said list.
iterates through the token list. */
char	*build_single_cmd(t_tokens **tokens, int index)
{
	char	*cmd;

	cmd = ft_strdup("");
	while ((*tokens)->index < index && (*tokens)->next)
		(*tokens) = (*tokens)->next;
	while ((*tokens)->type != 1 && (*tokens)->next)
	{
		if ((*tokens)->type != 7)
			strjoin_and_replace(&cmd, (*tokens)->token);
		if ((*tokens)->type == 7 && (*tokens)->next->type != 1)
			strjoin_and_replace(&cmd, " ");
		(*tokens) = (*tokens)->next;
	}
	if (!(*tokens)->next && (*tokens)->type == 0)
			strjoin_and_replace(&cmd, (*tokens)->token);
	return (cmd);
}

/* Builds an array of commands as char * */
char	**build_cmd_array(t_tokens *tokens)
{
	char	**cmds;
	int		i;
	int		nr_of_cmds;

	i = 0;
	nr_of_cmds = count_cmds(tokens);
	cmds = malloc((nr_of_cmds + 1) * sizeof(char *));
	while (i < nr_of_cmds)
	{
		if (tokens->type != 7)
		{
			if (tokens->type == 1)
			{
				cmds[i] = ft_strdup("|");
				if (tokens->next)
					tokens = tokens->next;
			}
			else
				cmds[i] = build_single_cmd(&tokens, i);
			i++;
		}
		else
		{
			if (tokens->next)
				tokens = tokens->next;
			else
				break;
		}
	}
	cmds[i] = 0;
	return (cmds);
}


void	print_cmds(char **cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
	{
		printf("%s ",cmds[i]);
		i++;
	}
	printf("\n");
}

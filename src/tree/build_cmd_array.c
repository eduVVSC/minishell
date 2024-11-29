/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 13:17:15 by dioferre          #+#    #+#             */
/*   Updated: 2024/11/29 14:51:26 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_cmds(t_tokens *tokens)
{
	int	i;

	i = 1;
	if (!tokens)
		return (0);
	while (tokens)
	{
		if (tokens->type != 0)
			i++;
		if (!tokens->next)
			break;
		tokens = tokens->next;
	}
	return (i);
}

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
		if (tokens->type == 0)
		{
			cmds[i] = ft_strdup("");
			while (tokens->next && tokens->type == 0)
			{
				cmds[i] = ft_strjoin(cmds[i], tokens->token);
				if (tokens->next && tokens->next->type == 0)
					cmds[i] = ft_strjoin(cmds[i], " ");
				tokens = tokens->next;
			}
			if (!tokens->next && tokens->type == 0)
				cmds[i] = ft_strjoin(cmds[i], tokens->token);
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

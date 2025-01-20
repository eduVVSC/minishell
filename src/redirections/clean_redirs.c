/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_redirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 18:03:47 by dioferre          #+#    #+#             */
/*   Updated: 2025/01/12 18:29:40 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* static int	count_cmd_tokens(char **cmd)
{
	int	i;
	int	tokens;

	i = 0;
	tokens = 0;
	while (cmd[i])
	{
		if (is_infile(cmd[i]) || is_outfile(cmd[i]))
			i += 2;
		else
		{
			tokens++;
			i++;
		}
	}
	return (tokens);
}

char	**clean_redirs(char **cmd)
{
	char	**new_cmd;
	int		new_cmd_tokens;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_cmd_tokens = count_cmd_tokens(cmd);
	new_cmd = malloc((new_cmd_tokens + 1) * sizeof(char * ));
	while (cmd[i])
	{
		if (is_infile(cmd[i]) || is_outfile(cmd[i]))
			i += 2;
		if (cmd[i])
		{
			new_cmd[j] = cmd[i];
			i++;
			j++;
		}
	}
	new_cmd[j] = 0;
	return(free(cmd), new_cmd);
} */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   001_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:59:53 by dioferre          #+#    #+#             */
/*   Updated: 2024/11/19 11:54:12 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Checks if there are opened quotes
returns, 1 if yes, 0 if not. */
int	check_open_quotes(char **args)
{
	// Might be just one pointer dont know yet lol.
	char	quote_type;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (args[i])
	{
		while(args[i][j])
		{
			if (args[i][j] == '\'' || args[i][j] == '\"')
			{
				if (handle_quotes(args[i], j, args[i][j]) == -1)
					return (true);
				j = handle_quotes(args[i], j, args[i][j]);
			}
			j++; // Will always increment cause hq function will set return the index of the quote.
		}
		i++;
	}
	return (false);
}


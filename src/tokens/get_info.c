/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:10:15 by dioferre          #+#    #+#             */
/*   Updated: 2025/01/20 13:13:12 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Returns a value based on the state of the given string.
int	get_token_state(char *str)
{
	int last_index;

	last_index = ft_strlen(str) - 1;
	if ((str[0] == '\'' || str[0] == '\"') && (str[last_index] == str[0]))
	{
		if (handle_quotes(str, 0, str[0]) != -1)
		{
			if (str[0] == '\'')
				return (1);
			else
				return (2);
		}
	}
	if (str[0] == '$')
		return (3);
	return (0);
}

// Returns a value based on the type of the given string.
int	get_token_type(char *str)
{
	if (ft_strlen(str) == 1)
	{
		if (*str == '|')
			return (PIPE);
		else if (*str == '<')
			return (INFILE);
		else if (*str == '>')
			return (TRU_OUTFILE);
	}
	else if (ft_strlen(str) == 2)
	{
		if (str[0] == '<' && str[1] == '<')
			return (HEREDOC);
		else if (str[0] == '>' && str[1] == '>')
			return (APP_OUTFILE);
	}
	else if (*str == '$')
		return (EXPANSION);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:10:15 by dioferre          #+#    #+#             */
/*   Updated: 2024/11/25 11:53:59 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Returns a value based on the state of the given string.
int	get_token_state(char *str)
{
	if (str[0] == '\'' || str[0] == '\"')
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
			return (1);
		else if (*str == '&')
			return (2);
		else if (*str == '<')
			return (3);
		else if (*str == '>')
			return (4);
	}
	else if (ft_strlen(str) == 2)
	{
		if (str[0] == '<' && str[1] == '<')
			return (5);
		else if (str[0] == '>' && str[1] == '>')
			return (4);
	}
	else if (*str == '$')
		return (6);
	return (0);
}

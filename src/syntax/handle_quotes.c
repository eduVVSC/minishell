/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 09:04:53 by dioferre          #+#    #+#             */
/*   Updated: 2025/02/25 13:26:59 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Looks for the next quote type in the string,
returns an index to that quote if found, -1 if none was found. */
int	handle_quotes(const char *str, int i, char quote_type)
{
	i++;
	while (str[i] != quote_type && str[i] != '\0')
		i++;
	if (str[i] != quote_type)
		return (-1);
	return (i);
}

int	is_separator(char c)
{
	if (c == ' ' || c == '\n') // Needs to include tabs and new lines too.
		return(1);
	return(0);
}

int	is_quote(char c)
{
	if (c == '\"' || c == '\'')
		return(1);
	return(0);
}

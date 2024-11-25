/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 09:04:53 by dioferre          #+#    #+#             */
/*   Updated: 2024/11/22 17:47:12 by dioferre         ###   ########.fr       */
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
	if (c == ' ') // Needs to include tabs and new lines too.
		return(1);
	return(0);
}

/* Counts words in a string
returns word nr or 0 if str is empty,
won't count anything in quotes as a word. */
int	word_count(char *str)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	if (!str || str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			i = handle_quotes(str, i, str[i]);
			if (i == -1)
				return (-1);
		}
		if (!is_separator(str[i]) &&
				(is_separator(str[i + 1]) || str[i + 1] == '\0'))
			words++;
		i++;
	}
	return (words);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 09:04:53 by dioferre          #+#    #+#             */
/*   Updated: 2024/11/17 15:26:54 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>

/* Looks for the next quote type in the string,
returns an index to that quote if found, -1 if none was found,
Flag: 0 if single quote; 1 if double quote. */
int	handle_quotes(const char *str, int i, char quote_type)
{
	i++;
	while (str[i] != quote_type && str[i] != '\0')
		i++;
	if (str[i] != quote_type)
		return (-1);
	return (i);
}

/* Counts words in a string based on a given separator
returns word nr or 0 if str is empty. */
int	word_count(char *str, char separator)
{
	int	i;
	int	words;

	i = 0;
	words = 1;
	if (!str || str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] == separator)
			words++;
		i++;
	}
	return (words);
}

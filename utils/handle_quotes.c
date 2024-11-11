/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 09:04:53 by dioferre          #+#    #+#             */
/*   Updated: 2024/11/11 13:53:40 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

/* Looks for the next quote type in the string,
returns an index to that quote if found, -1 if none was found,
Flag: 0 if single quote; 1 if double quote. */
int	handle_quotes(const char *str, int i, short flag)
{
	char	quote_type;

	i++;
	if (flag == 0)
		quote_type = '\'';
	else
		quote_type = '\"';
	printf("teste\n");
	while (str[i] != quote_type && str[i] != '\0')
		i++;
	if (str[i] != quote_type)
		return (-1);
	return (i);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 09:04:53 by dioferre          #+#    #+#             */
/*   Updated: 2024/11/11 09:14:19 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Looks for the next quote type in the string,
returns an index to that quote if found, -1 if none was found,
Flag: 0 if single quote; 1 if double quote. */
int	handle_quotes(const char *str, int i, short flag)
{
	char	quote_type;
	int		close_quote;

	close_quote = 0;
	if (flag == 0)
		quote_type = '\'';
	else
		quote_type = '\"';
	while (str[i + close_quote] != quote_type || str[i + close_quote] == '\0')
		close_quote++;
	if (str[i + close_quote] != quote_type)
		return (-1);
	return (close_quote);
}

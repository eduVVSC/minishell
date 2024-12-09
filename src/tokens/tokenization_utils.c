/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 09:26:24 by dioferre          #+#    #+#             */
/*   Updated: 2024/12/09 14:02:12 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Creates a token with a space in it.
void	create_space_token(t_tokens *tokens)
{
	tokens->token = ft_strdup(" ");
	tokens->state = 0;
	tokens->type = 7;
}

// Counts the ammount of spaces in the string,
// it counts as a group of continuos spaces as a single one.
int	count_spaces(char *str)
{
	int	i;
	int	spaces;

	i = 0;
	spaces = 0;
	while (str[i] == ' ')
		i++;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			i = handle_quotes(str, i, str[i]);
		if (str[i] == ' ')
		{
			while (str[i] == ' ')
				i++;
			if (str[i] != 0)
				spaces++;
		}
		else
			i++;
	}
	return (spaces);
}

// Counts how many quotes should be taken off from the given sring.
int	count_quotes_to_take_off(char *str)
{
	char	quote_searching;
	int		nr_of_quotes;
	int		i;

	i = 0;
	nr_of_quotes = 0;
	quote_searching = '\0';
	while (str[i])
	{
		if(quote_searching == '\0' && (str[i] == 34 || str[i] == 39)) // doble e single quote
		{
			quote_searching = str[i];
			nr_of_quotes++;
		}
		else if(str[i] == quote_searching)
		{
			quote_searching = '\0';
			nr_of_quotes++;
		}
		i++;
	}
	return (nr_of_quotes);
}

// Cleans the quotes from the given string so it functions the same as bash.
char	*clean_tkn_quotes(char *str)
{
	char	*cmd;
	int		quotes_to_wipe;
	int		i;
	int		j;
	int		close_quote;

	i = 0;
	j = 0;
	close_quote = 0;
	quotes_to_wipe = count_quotes_to_take_off(str);
	cmd = (char *)malloc((ft_strlen(str) - quotes_to_wipe + 1) * sizeof(char));
	while(str[j])
	{
		if (is_quote(str[j]))
		{
			close_quote = handle_quotes(str, j, str[j]); // gets the index of where the closed quote is.
			j++;
			while (j < close_quote) // iterates and copies the chars in the string until it finds the closed quote;
				cmd[i++] = str[j++];
			continue;
		}
		cmd[i++] = str[j++];
	}
	cmd[i] = 0;
	return(free(str), cmd);
}

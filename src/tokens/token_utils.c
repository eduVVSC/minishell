/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 09:26:24 by dioferre          #+#    #+#             */
/*   Updated: 2025/02/10 15:25:53 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// lol
int	is_redir(char c)
{
	if (c == '>' || c == '<')
		return (1);
	return (0);
}

// Helper function for get_token_len
void	set_quote_state(char c, int *quote_state)
{
	if (*quote_state == GENERAL)
	{
		if (c == '\'')
			*quote_state = SINGLE_QUO;
		else if (c == '\"')
			*quote_state = DOUBLE_QUO;
	}
	else if (*quote_state == SINGLE_QUO)
	{
		if (c == '\'')
			*quote_state = GENERAL;
	}
	else if (*quote_state == DOUBLE_QUO)
	{
		if (c == '\"')
			*quote_state = GENERAL;
	}
}

int	are_there_more_tokens(char *input)
{
	while (is_separator(*input))
		*input++;
	if (*input)
		return (1);
	return (0);
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
	if (quotes_to_wipe == 0)
		return (str);
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

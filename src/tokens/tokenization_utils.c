/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 09:26:24 by dioferre          #+#    #+#             */
/*   Updated: 2024/12/02 12:05:19 by dioferre         ###   ########.fr       */
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
			spaces++;
			while (str[i] == ' ')
				i++;
		}
		else
			i++;
	}
	return (spaces);
}

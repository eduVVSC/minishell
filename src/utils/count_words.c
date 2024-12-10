/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:29:28 by dioferre          #+#    #+#             */
/*   Updated: 2024/12/09 15:33:58 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_words(char *str)
{
	int	words;
	int	i;

	words = 1;
	i = 0;
	if (!str)
		return (-1);
	while(is_separator(str[i]))
		i++;
	if (str[i] == 0)
		return (0);
	while(str[i])
	{
		while(is_separator(str[i]))
			i++;
		if (!is_separator(str[i]))
		{
			i++;
			words++;
		}
	}
	return (words);
}

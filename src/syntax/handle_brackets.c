/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_brackets.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:37:40 by dioferre          #+#    #+#             */
/*   Updated: 2024/11/19 12:37:41 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Checks if a char is a bracket
returns the ascii value if so, 0 if not. */
int	is_bracket(char c)
{
	if (c == '(' || c == '{' || c == '[')
		return (c);
	return (false);
}

/* Checks for open bracks in the string
returns 1 if there are, 0 if not. */
int	check_open_brackets(const char *str)
{
	int		i;
	int		j;
	char	bracket_type;
	char	closed_bracket;

	i = 0;
	j = 1;
	while (str[i])
	{
		if (is_bracket(str[i]))
		{
			bracket_type = str[i];
			if (bracket_type == '(')
				closed_bracket = ')';
			else
				closed_bracket = bracket_type + 2;
			while (str[i + j] && str[i + j] != closed_bracket)
				j++;
			if (str[i + j] == '\0')
				return (true);
		}
		i++;
	}
	return (false);
}

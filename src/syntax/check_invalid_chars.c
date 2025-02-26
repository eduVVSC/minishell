/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_invalid_chars.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvieira <edvieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:23:03 by edvieira          #+#    #+#             */
/*   Updated: 2025/02/26 14:24:31 by edvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Will check the use of '!' in a input
/// @param input
/// @param pos
/// @param val_num
/// @return (true(1) -> good use of exclamation)
/// @return (false(0) -> bad use of exclamation)
int	exclamation_validation(char *input, int pos, int val_num)
{
	if ((input[pos] == '!'
			&& input[pos + 1] == '\'' && val_num == single_quo))
		return (true);
	else if ((input[pos] == '!'
			&& input[pos + 1] == '\"' && val_num == double_quo))
		return (true);
	else if (input[pos] == '!'
		&& (input[pos + 1] != ' ' && input[pos + 1] != '\0'))
	{
		ft_putstr_fd("minishell: event not found\n", 2);
		return (false);
	}
	return (true);
}

void	parenthesis_validation(char *input, int pos)
{
	ft_putstr_fd("minishell: syntax error near unexpected token '", 2);
	ft_putchar_fd(input[pos], 2);
	ft_putstr_fd("'\n", 2);
}

int	check_invalid_chars(char *input, int i)
{
	int	val_num;

	val_num = GENERAL;
	while (input[i])
	{
		if ((input[i] == '(' || input[i] == ')') && val_num == GENERAL)
			return (parenthesis_validation(input, i), 0);
		else if (exclamation_validation(input, i, val_num) == false)
			return (0);
		else if ((input[i] == '\\' || input[i] == ';') && val_num == GENERAL)
			return (print_syntax_error(INVALID_CHAR_ERROR), 0);
		i++;
	}
	return (1);
}

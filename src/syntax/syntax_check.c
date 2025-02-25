/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:41:15 by dioferre          #+#    #+#             */
/*   Updated: 2025/02/25 13:44:05 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	is_valid_input(char *input, int character_check)
{
	int	i;

	i = -1;
	while (input[++i])
	{
		if (is_normal_char(input[i]) && !character_check)
			character_check = TRUE;
		else if (input[i] == '|')
		{
			if (has_double_pipe(input, i + 1) == -1 || !character_check)
				return (print_syntax_error(OPEN_PIPE_ERROR), FALSE);
		}
		else if (is_quote(input[i]))
		{
			i = handle_quotes(input, i, input[i]);
			if (i == -1)
				return (print_syntax_error(OPEN_QUOTE_ERROR), 0);
			character_check = TRUE;
		}
		else if (is_forbidden_char(input[i]))
			return(check_invalid_chars(input, i));
	}
	if (!character_check)
		return (print_syntax_error(UNEXPECTED_TOKEN), 0);
	return (TRUE);
}

int	check_syntax(t_shell *shell, char *input)
{
	if (!input)
		exit (clean_all_and_close(shell));
	else if (input[0] == '\0' || input[0] == '\n')
		return (-1);
	else if (!is_valid_input(input, 0))
		return (-1);
	else
		return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:41:15 by dioferre          #+#    #+#             */
/*   Updated: 2025/02/10 17:16:25 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_double_pipe(char *input, int i)
{
	while (input[i])
	{
		if (input[i] == '|')
			return (-1);
		else if (!is_separator(input[i])
			&& (input[i] != '<' && input[i] != '>'))
			return (0);
		i++;
	}
	return (0);
}

int	is_forbidden_char(char c)
{
	if (c == '\\' || c == ';'
		|| c == '(' || c == ')'
		|| c == '{' || c == '}'
		|| c == '[' || c == ']'
		|| c == '&' || c == '!')
		return (TRUE);
	return (FALSE);
}


int	check_syntax(t_shell *shell, char *input)
{
	int	i;

	i = 0;
	if (!input)
		exit (clean_all_and_close(shell));
	if (input[0] == '\0' || input[0] == '\n')
		return (-1);
	while (input[i])
	{
		if (input[i] == '|')
		{
			if (has_double_pipe(input, i + 1) == -1)
				return (print_syntax_error(OPEN_PIPE_ERROR), -1);
		}
		else if (is_quote(input[i]))
		{
			i = handle_quotes(input, i, input[i]);
			if (i == -1)
				return (print_syntax_error(OPEN_QUOTE_ERROR), -1);
		}
		else if (is_forbidden_char(input[i]))
			return(check_invalid_chars(input, i));
		i++;
	}
	return (0);
}

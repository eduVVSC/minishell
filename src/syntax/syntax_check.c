/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvieira <edvieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:41:15 by dioferre          #+#    #+#             */
/*   Updated: 2025/03/15 15:29:19 by edvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_valid_redir(char *input, int i, char c)
{
	int		redir_count;

	redir_count = 1;
	while (input[++i])
	{
		if (is_normal_char(input[i]))
			return (TRUE);
		else if (is_redir(input[i]))
		{
			if (input[i] == c)
				redir_count++;
			else if (redir_count > 2 || input[i] != c)
				return (FALSE);
		}
		else if (is_quote(input[i]))
		{
			i = handle_quotes(input, i, input[i]);
			if (i == -1)
				return (FALSE);
			return (TRUE);
		}
		else if (input[i] == '|')
			break ;
	}
	return (FALSE);
}

int	check_valid_pipe(char *input, int i)
{
	while (input[i])
	{
		if ((!is_separator(input[i]) && !is_redir(input[i])
				&& input[i] != '|'))
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int	is_valid_input(char *input)
{
	int	i;

	i = -1;
	while (input[++i])
	{
		if (is_quote(input[i]))
		{
			i = handle_quotes(input, i, input[i]);
			if (i == -1)
				return (print_syntax_error(OPEN_QUOTE_ERROR), 0);
		}
		else if (is_redir(input[i]) && !(check_valid_redir(input, i, input[i])))
			return (print_syntax_error(UNEXPECTED_TOKEN), 0);
		else if (input[i] == '|')
		{
			if (has_double_pipe(input, i + 1) == -1
				|| !check_valid_pipe(input, i))
				return (print_syntax_error(OPEN_PIPE_ERROR), FALSE);
		}
	}
	return (TRUE);
}

int	is_input_only_separators(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (!is_separator(input[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	check_syntax(t_shell *shell, char *input)
{
	if (!input)
		exit (clean_all_and_close(shell));
	else if (input[0] == '\0' || input[0] == '\n')
		return (-1);
	else if (is_input_only_separators(input))
		return (0);
	else if (!is_valid_input(input))
		return (-1);
	else
		return (0);
}

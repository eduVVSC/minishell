/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:47:58 by dioferre          #+#    #+#             */
/*   Updated: 2025/02/25 13:08:07 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	syntax_pipe_error(void)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
}

void	syntax_open_quote_error(void)
{
	ft_putstr_fd("minishell: syntax error: unclosed quotes\n", 2);
}

void	syntax_invalid_char_error(void)
{
	ft_putstr_fd("minishell: syntax error: ", 2);
	ft_putstr_fd("invalid char detected, '\\' and ';' not supported.\n", 2);
}

void	syntax_unexpected_token_error(void)
{
	ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
}

void	print_syntax_error(int error_num)
{
	if (error_num == OPEN_PIPE_ERROR)
		syntax_pipe_error();
	else if (error_num == OPEN_QUOTE_ERROR)
		syntax_open_quote_error();
	else if (error_num == INVALID_CHAR_ERROR)
		syntax_invalid_char_error();
	else if (error_num == UNEXPECTED_TOKEN)
		syntax_unexpected_token_error();
}

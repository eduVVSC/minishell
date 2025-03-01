/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvieira <edvieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:29:26 by dioferre          #+#    #+#             */
/*   Updated: 2025/03/01 17:47:21 by edvieira         ###   ########.fr       */
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

/* int	is_forbidden_char(char c)
{
	if (c == '\\' || c == ';'
		|| c == '(' || c == ')'
		|| c == '{' || c == '}'
		|| c == '[' || c == ']'
		|| c == '&' || c == '!')
		return (TRUE);
	return (FALSE);
} */

int	is_normal_char(char c)
{
	if (!is_separator(c) && !is_redir(c)
		//	&& !is_forbidden_char(c)
		&& c != '|'
		&& !is_quote(c))
		return (TRUE);
	return (FALSE);
}

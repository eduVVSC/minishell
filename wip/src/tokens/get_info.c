/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:10:15 by dioferre          #+#    #+#             */
/*   Updated: 2024/11/22 18:19:27 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_token_state(char *str)
{
	if (str[0] == '\'' || str[0] == '\"')
	{
		if(handle_quotes(str, 0, str[0]) != -1)
		{
			if (str[0] == '\'')
				return (1);
			else
				return (2);
		}
	}
	if (str[0] == '$')
		return (3);
	return (0);
}

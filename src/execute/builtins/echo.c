/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:48:28 by dioferre          #+#    #+#             */
/*   Updated: 2024/11/29 14:48:29 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	setting_to_print(char **command)
{
	int	i;

	i = 1;
	while(command[i])
	{
		if (check_expand(command[i]) != -1)
			command[i] = handle_expension(command[i]);
		i++;
	}
}

void	do_echo(char **command)
{
	setting_to_print(command);

	execve(command[0], command, NULL);
}

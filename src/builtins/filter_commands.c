/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvieira <edvieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:44:39 by dioferre          #+#    #+#             */
/*   Updated: 2025/02/27 16:18:01 by edvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// need to handle only enter
int	is_builtin( t_shell *shell, char **command)
{
	int	exit_code;

	exit_code = 0;
	if (ft_strcmp(command[0], "echo") == 0)
		exit_code = do_echo(command);
	else if (ft_strcmp(command[0], "pwd") == 0)
		exit_code = do_pwd(command);
	else if (ft_strcmp(command[0], "env") == 0)
		exit_code = do_env(command, shell->env);
	else
		return (-1);
	ft_free_double_arr(&command);
	return (exit_code);
}

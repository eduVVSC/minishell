/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleCommands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvieira <edvieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:44:39 by dioferre          #+#    #+#             */
/*   Updated: 2025/01/03 18:16:39 by edvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// need to handle only enter
int	is_builtin( t_shell *shell, char **command)
{
	if (ft_strcmp(command[0], "echo") == 0)
		do_echo(command);
	else if (ft_strcmp(command[0], "pwd") == 0) // seems to be working well now!!
		printf("Function return |%d|\n",do_pwd(command));
	else if (ft_strcmp(command[0], "cd") == 0) // seems to be working well now!!
		printf("Function return |%d|\n",do_cd(shell, command));
	else if (ft_strcmp(command[0], "export") == 0) // seems to be working well now!!
		printf("Function return |%d|\n",do_export(&shell->env, command));
	else if (ft_strcmp(command[0], "env") == 0) // seems to be working well now!!
		printf("Function return |%d|\n",do_env(command, shell->env));
	else if (ft_strcmp(command[0], "unset") == 0) // last one!!
		printf("Function return |%d|\n", do_unset(shell->env, command));
	else
		return(0);
	return (1);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:44:39 by dioferre          #+#    #+#             */
/*   Updated: 2024/11/29 14:52:16 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Print the error message in the stderror
/// @return (127) exit_code for error
int	handle_env_error(char *command)
{
	ft_putstr_fd("env: Take no options or arguments\n", 2);
	return (127);
}

/// @brief Print all the env var with the "=" in the enviroment list
void	print_env(t_env *env)
{
	if (!env->var_name || env->var_name == NULL)
	{
		return ;
	}
	while (env != NULL)
	{
		if (env->operant != 0)
		{
			ft_printf("%s", env->var_name);
			ft_printf("%s", env->operant);
			ft_printf("%s\n", env->var_value);
		}
		env = env->next;
	}
}

/// @brief do the env function without arguments
/// @return (0) succes (127) error
int	do_env(char **command, t_env *env)
{
	if (check_exist_optionals(command) != 1)
		return (handle_env_error(command[1]));
	print_env(env);
	return (0);
}

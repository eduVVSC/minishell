/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvieira <edvieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:44:39 by dioferre          #+#    #+#             */
/*   Updated: 2025/02/11 14:59:58 by edvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Will deliver the error message
/// @brief to the stderror and return the exit code
/// @return (2 error)
int	handle_pwd_error(char **command)
{
	char	*message;

	message = ft_strjoin("bash: pwd: ", command[1]);
	message = ft_strjoin_free_s1(message, ": invalid option\n");
	ft_putstr_fd(message, 2);
	free (message);
	return (2);
}

/// @brief Do the pwd command without optionals
/// @return (0 success) (2 error)
int	do_pwd(char **command)
{
	char	*directory;

	if (check_exist_optionals(command) == -1)
		return (handle_pwd_error(command));
	directory = getcwd(NULL, 0);
	if (directory == NULL)
		return (-1);
	ft_printf("%s\n", directory);
	free (directory);
	return (0);
}

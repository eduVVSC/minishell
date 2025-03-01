/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvieira <edvieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 16:52:51 by edvieira          #+#    #+#             */
/*   Updated: 2025/03/01 16:56:57 by edvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief takes the given path and return the
/// @brief type of file it is to deliver the proper error message.
/// @return (3 -> no file) (2-> dir without permission) (1-> not a dir)
int	check_file_type(char *dir_path)
{
	struct stat		statbuf;

	if (stat(dir_path, &statbuf) == -1)
		return (3);
	if (S_ISDIR(statbuf.st_mode))
		return (1);
	else
		return (2);
}

/// @brief Will deliver the error message to the
/// @brief stderror and return the exit code
/// @return (2 -> error)
int	handle_cd_error(char **command)
{
	int		type;
	char	*message;

	type = check_file_type(command[1]);
	message = ft_strjoin("bash: cd: ", command[1]);
	if (type == 1)
		message = ft_strjoin_free_s1(message, ": Permission denied\n");
	else if (type == 2)
		message = ft_strjoin_free_s1(message, ": Not a directory\n");
	else if (type == 3)
		message = ft_strjoin_free_s1(message, ": No such file or directory\n");
	ft_putstr_fd(message, 2);
	free (message);
	return (1);
}

/// @brief Start the variable temp as the new pwd variable
/// @param temp
void	start_pwd(t_env *temp)
{
	temp->var_name = ft_strdup("PWD");
	temp->operant = ft_strdup("=");
	temp->var_value = getcwd(NULL, 0);
	if (!temp->var_value)
		temp->var_value = ft_strdup("");
	temp->next = NULL;
	temp->printed = 0;
	if (temp->operant[0] == '=')
		temp->behaviour = 0;
	else
		temp->behaviour = 1;
}

/// @brief starts the variable as the new oldpwd variable
/// @param temp
/// @param old_pwd_value
void	start_old_pwd(t_env *temp, char *old_pwd_value)
{
	temp->var_name = ft_strdup("OLDPWD");
	temp->operant = ft_strdup("=");
	temp->var_value = old_pwd_value;
	if (!temp->var_value)
		temp->var_value = ft_strdup("");
	temp->next = NULL;
	temp->printed = 0;
	if (temp->operant[0] == '=')
		temp->behaviour = 0;
	else
		temp->behaviour = 1;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:30:50 by dioferre          #+#    #+#             */
/*   Updated: 2025/02/03 18:27:00 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_for_cmd_errors(char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) == -1)
		return (127);
	else if (S_ISREG(path_stat.st_mode) && access(path, X_OK) == -1)
		return (126);
	else if (S_ISDIR(path_stat.st_mode))
		return (128); // Should return 126 but need a way to differanciate them for error messages.
	else if (access(path, R_OK) == -1)
		return (127);
	return (0);
}

int	print_execve_error(char *cmd, int error_code)
{
	// ERROR MSGS VARY DEPENDING ON IF THE CMD STARTS W './' OR '/' GOTTA CHECK THIS LATER
	if (error_code == 127)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
		return (error_code);
	}
	else if (error_code == 126)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": permission denied\n", 2);
		return (error_code);
	}
	else if (error_code == 128)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": is a directory\n", 2);
		return (126);
	}
	return (0);
}

void	exec_cmd(t_shell *shell, t_tokens *node_content)
{
	char	**cmd;
	char	*path;
	char	**envp;
	int		error;

	cmd = build_cmd(&node_content);
 	if (!is_builtin(shell, cmd))
	{
		path = find_path(cmd[0], shell->env);
		envp = transfrom_env_to_array(shell->env);
		if (!path) // gotta check if this is really necessary.
			path = ft_strdup(cmd[0]);
		error = check_for_cmd_errors(path);
		if (!error && ft_strncmp(cmd[0], "./", 2))
			error = execve(path, cmd, envp);
		else
		{
			if (!error)
				error = execve(cmd[0], cmd, envp);
		}
		error = print_execve_error(cmd[0], error);
		free(path);
		ft_free_double_arr(&envp);
		ft_free_double_arr(&cmd);
		clean_and_terminate_with_status(shell, error);
	}
	clean_and_terminate_with_status(shell, 0);
}

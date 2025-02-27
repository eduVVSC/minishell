/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvieira <edvieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:30:50 by dioferre          #+#    #+#             */
/*   Updated: 2025/02/27 16:17:53 by edvieira         ###   ########.fr       */
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

void	print_executable_errors(char *cmd, int error_code)
{
	if (error_code > 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		if (error_code == 127)
			ft_putstr_fd(": No such file or directory\n", 2);
		else if (error_code == 126)
			ft_putstr_fd(": Permission denied\n", 2);
		else if (error_code == 128)
			ft_putstr_fd(": Is a directory\n", 2);
	}
}

int	print_cmd_errors(char *cmd, int error_code)
{
	if (error_code > 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		if (error_code == 127)
		{
			if (cmd[ft_strlen(cmd) - 1] == '/' || cmd[0] == '/')
				ft_putstr_fd(": No such file or directory\n", 2);
			else
				return (ft_putstr_fd(": Command not found\n", 2), 127);
		}
		else if (error_code == 126)
			return (ft_putstr_fd(": Command not found\n", 2), 127);
		else if (error_code == 128)
		{
			if ((ft_strlen(cmd) > 0 && cmd[ft_strlen(cmd) - 1] == '/')
					|| cmd[0] == '/')
				ft_putstr_fd(": Is a directory\n", 2);
			else
				return (ft_putstr_fd(": Command not found\n", 2), 127);
		}
	}
	return (error_code);
}

int	print_execve_error(char *path, char *cmd, int error_code)
{
	if (error_code != 0)
	{
		if (!ft_strncmp(cmd, "./", 2))
			print_executable_errors(cmd, error_code);
		else
			error_code = print_cmd_errors(cmd, error_code);
		if (error_code == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": Command not found\n", 2);
			error_code = 127;
		}
		if (error_code == 128)
			error_code = 126;
		return (error_code);
	}
	return (0);
}

void	exec_cmd(t_shell *shell, t_tokens *node_content)
{
	char	**cmd;
	char	**envp;
	char	*path;
	int		error;

	cmd = build_cmd(&node_content);
	error = is_builtin(shell, cmd);
 	if (error == -1)
	{
		path = find_path(cmd[0], shell->env);
		envp = transfrom_env_to_array(shell->env);
		error = check_for_cmd_errors(path);
		if (!error && (ft_strncmp(cmd[0], "./", 2) && ft_strncmp(cmd[0], "/", 1)))
			error = execve(path, cmd, envp);
		else if (!error)
				error = execve(cmd[0], cmd, envp);
		error = print_execve_error(path, cmd[0], error);
		free(path);
		ft_free_double_arr(&envp);
		ft_free_double_arr(&cmd);
	}
	clean_and_terminate_with_status(shell, error);
}

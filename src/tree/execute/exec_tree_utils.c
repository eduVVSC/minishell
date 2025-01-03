/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:11:15 by dioferre          #+#    #+#             */
/*   Updated: 2025/01/03 16:03:03 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Looks for the path of a given command,
returns a NULL str if it wasn't found. */
char	*find_path(char *cmd, t_env *envp)
{
	// Imported from pipex, need to see if this works lol, lmao.
	char	**paths;
	char	*part_path;
	char	*path;
	int		i;

	i = 0;
	path = get_env_var_value(envp, "PATH");
	//if (path == NULL)
	//
	paths = ft_split(path, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
		{
			ft_free_double_arr(&paths);
			return (path);
		}
		free(path);
		i++;
	}
	ft_free_double_arr(&paths);
	return (NULL);
}

/* Checks if the given command is a builtin,
and if so, executes it. */
void	check_if_builtin(char **cmd, char *envp)
{

}

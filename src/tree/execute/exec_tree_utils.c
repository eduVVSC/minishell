/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:11:15 by dioferre          #+#    #+#             */
/*   Updated: 2024/12/22 16:40:37 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Looks for the path of a given command,
returns a NULL str if it wasn't found. */
char	*find_path(char *cmd, char **envp)
{
	// Imported from pipex, need to see if this works lol, lmao.
	char	**paths;
	char	*part_path;
	char	*path;
	int		i;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
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

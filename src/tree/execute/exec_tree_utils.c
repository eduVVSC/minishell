/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:11:15 by dioferre          #+#    #+#             */
/*   Updated: 2025/01/10 12:25:21 by dioferre         ###   ########.fr       */
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
	if (path == NULL)
		return (NULL);
	paths = ft_split(path, ':');
	i = -1;
	while (paths[++i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin_free_s1(part_path, cmd);
		if (access(path, F_OK) == 0)
			break ;
		free(path);
		path = NULL;
	}
	ft_free_double_arr(&paths);
	return (path);
}

// Checks if a command has a redirection in it lol, lmao
// @return 0, 1, 2 or 3 depending on the redir found.
int	has_redirection(t_tokens *tokens)
{
	while (tokens)
	{
		if ((tokens->type == INFILE
			|| tokens->type == HEREDOC
			|| tokens->type == OUTFILE)
			&& tokens->state == general)
			return (1);
		tokens = tokens->next;
	}
	return(0);
}

// Opens a file and returns the fd.
// Flags: 0 Append, 1 truncate, 2 read.
int	open_file(char *file_name, int flag)
{
	int	file;

	file = 0;
	if (flag == 1)
		file = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (flag == 2)
		file = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (flag == 3)
		file = open(file_name, O_RDONLY, 0777);
	if (file == -1)
		printf("open file error lol!\n");
	return (file);
}

// @return Length of a matrix
int	get_matrix_len(char **matrix)
{
	int	i;

	i = 0;
	if (!matrix[0] || !matrix)
		return (0);
	while (matrix[i])
		i++;
	return (i);
}

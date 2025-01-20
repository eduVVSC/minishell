/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 15:04:23 by dioferre          #+#    #+#             */
/*   Updated: 2025/01/12 18:03:41 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include "minishell.h"

int	is_infile(char *str)
{
	if (!strcmp(str, "<"))
		return (1);
	return (0);
}

int	is_outfile(char *str)
{
	if (!strcmp(str, ">") || !strcmp(str, ">>"))
		return (1);
	return (0);
}

void	dup_from_input(int fd)
{
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	dup_to_output(int fd)
{
	dup2(fd, STDOUT_FILENO);
	close(fd);
}
 */

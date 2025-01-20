/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 15:04:23 by dioferre          #+#    #+#             */
/*   Updated: 2025/01/20 13:02:00 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

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


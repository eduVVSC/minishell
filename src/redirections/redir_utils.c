/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvieira <edvieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 15:04:23 by dioferre          #+#    #+#             */
/*   Updated: 2025/02/26 14:18:23 by edvieira         ###   ########.fr       */
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

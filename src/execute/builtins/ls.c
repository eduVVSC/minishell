/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:48:36 by dioferre          #+#    #+#             */
/*   Updated: 2024/11/29 14:48:36 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_ls(char **command)
{
	execve(command[0], command, NULL);
}

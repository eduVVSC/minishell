/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 13:18:17 by dioferre          #+#    #+#             */
/*   Updated: 2024/12/02 13:23:17 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmds	*build_cmd_list(char **cmds)
{
	t_cmds *cmd_list;
	t_cmds *head;
	int	i;

	i = 0;
	head = malloc(sizeof(t_cmds));
	cmd_list = head;
	while (cmds[i])
	{
		if (i != 0)
			cmd_list = malloc(sizeof(t_cmds));
		cmd_list->cmd = ft_split(cmds[i], ' ');
		cmd_list->cmd[0] = ft_strjoin("/bin/", cmd_list->cmd[0]);
		print_cmds(cmd_list->cmd);
		cmd_list->next = NULL;
		cmd_list = cmd_list->next;
		i++;
	}
	ft_free_double_arr(&cmds);
	return(head);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleCommands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:44:39 by dioferre          #+#    #+#             */
/*   Updated: 2025/01/03 16:22:15 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(t_cmds *cmd)
{
	t_cmds	*tmp;

	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		ft_free_double_arr(&tmp->cmd);
		free(tmp);
	}
}


// need to handle only enter
int	is_builtin( t_shell *shell, char **command)
{
	//printf("command now = |%s|\n", command[0]);
	/*if (ft_strcmp(command[0], "") == 0 || ft_strcmp(command[0], "/bin/") == 0)
		printf("Function return |127|\n"); */
	if (ft_strcmp(command[0], "echo") == 0)
		do_echo(command);
	else if (ft_strcmp(command[0], "pwd") == 0) // seems to be working well now!!
		printf("Function return |%d|\n",do_pwd(command));
	else if (ft_strcmp(command[0], "cd") == 0) // seems to be working well now!!
		printf("Function return |%d|\n",do_cd(shell, command));
	else if (ft_strcmp(command[0], "export") == 0) // seems to be working well now!!
		printf("Function return |%d|\n",do_export(&shell->env, command));
	else if (ft_strcmp(command[0], "env") == 0) // seems to be working well now!!
		printf("Function return |%d|\n",do_env(command, shell->env));
	else if (ft_strcmp(command[0], "unset") == 0) // last one!!
		printf("Function return |%d|\n", do_unset(shell->env, command));
	else
		return(0);
	return (1);

}

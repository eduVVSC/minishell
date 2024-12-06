/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleCommands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:44:39 by dioferre          #+#    #+#             */
/*   Updated: 2024/11/29 14:52:16 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	handle_commands(t_tokens *tokens, t_env *env, char **envp)
{
	t_cmds	*cmds_list;
	t_tokens *tmp;

	cmds_list = build_cmd_list(build_cmd_array(tokens));
	while (tokens)
	{
		tmp = tokens->next;
		free (tokens->token);
		free (tokens);
		tokens = tmp;
	}
	cmd(cmds_list->cmd);
	// EXECUTE TREE(each element receive the cmd)
}

void	cmd(char **command)
{
	int	len_command;
	int	retorno;

	len_command = ft_strlen(command[0]);
 	if (ft_strncmp(command[0], "/bin/cd", len_command) == 0)
		do_cd(command);
	else
		retorno = execve(command[0], command, NULL);
	printf("%d\n", retorno);
/* 	if(ft_strncmp(command[0], "/bin/pwd", len_command) == 0)
		do_pwd(command);
	else if(ft_strncmp(command[0], "/bin/ls", len_command) == 0)
		do_ls(command);
	else if(ft_strncmp(command[0], "/bin/echo", len_command) == 0)
		do_echo(command); */

	/*else if(ft_strncmp(command[0], "export", len_command) == 0)
		do_export(command);
	else if(ft_strncmp(command[0], "unset", len_command) == 0)
		do_unset(command);
	else if(ft_strncmp(command[0], "exit", len_command) == 0)
		do_exit(command);
	else if(ft_strncmp(command[0], "env", len_command) == 0)
		do_env(command);
*/
}

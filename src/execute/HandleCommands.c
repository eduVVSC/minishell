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

<<<<<<< HEAD

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

	len_command = ft_strlen(command[0]);
	if(ft_strncmp(command[0], "/bin/pwd", len_command) == 0)
		do_pwd(command);
	else if(ft_strncmp(command[0], "/bin/ls", len_command) == 0)
		do_ls(command);
	else if(ft_strncmp(command[0], "/bin/echo", len_command) == 0)
		do_echo(command);
 	else if(ft_strncmp(command[0], "/bin/cd", len_command) == 0)
		do_cd(command);
	/*else if(ft_strncmp(command[0], "export", len_command) == 0)
		do_export(command);
	else if(ft_strncmp(command[0], "unset", len_command) == 0)
		do_unset(command);
	else if(ft_strncmp(command[0], "exit", len_command) == 0)
		do_exit(command);
	else if(ft_strncmp(command[0], "env", len_command) == 0)
		do_env(command);
*/
=======
void	cmd(char **command)
{
	int	len_command;

	len_command = ft_strlen(command[0]);
	if(ft_strncmp(command[0], "/bin/ls", len_command) == 0) // do first
		do_ls(command);
	else if(ft_strncmp(command[0], "pwd", len_command) == 0) // do first
		do_pwd(command);
	else if(ft_strncmp(command[0], "echo", len_command) == 0)
		do_echo(command);
 	else if(ft_strncmp(command[0], "cd", len_command) == 0)
		do_cd(command);
	/*else if(ft_strncmp(command[0], "export", len_command) == 0)
		do_export(command);
	else if(ft_strncmp(command[0], "unset", len_command) == 0)
		do_unset(command);
	else if(ft_strncmp(command[0], "exit", len_command) == 0) // do first
		do_exit(command);
	else if(ft_strncmp(command[0], "env", len_command) == 0) // do first
		do_env(command);
*/
}

int	count_dependencies(t_tokens *tokens)
{
	int	i;

	i = 1;
	while(tokens->next != NULL)
	{
		if(ft_strncmp(tokens->token, "|", 1) == 0)
			break;
		tokens = tokens->next;
		i++;
	}
	return (i);
}

void	*fullfill_command(t_tokens *tokens, int until_where, char **full_command)
{
	int	i;

	i = 0;
	while(i < until_where)
	{
		full_command[i] = ft_strdup(tokens->token);
		tokens = tokens->next;
		i++;
	}
	full_command[i] = NULL;
}

void print_command(char **command)
{
	int	i = 0;

	while(command[i])
	{
		printf("%s\n", command[i]);
		i++;
	}
}

void handle_commands(t_tokens *tokens, t_env *env, char **envp)
{
	int		many_dependencies;
	int		execve_return;
	char	**full_command;

	many_dependencies = count_dependencies(tokens);
	full_command = malloc(sizeof(char *) * (many_dependencies + 1));
	fullfill_command(tokens, many_dependencies, full_command);
	//print_command(full_command);
	//printf("--------------------\n");
	cmd(full_command);
	printf("%d : %s\n", execve_return, tokens->token);

>>>>>>> main
}

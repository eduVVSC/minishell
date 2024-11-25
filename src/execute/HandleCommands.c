/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleCommands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:44:39 by dioferre          #+#    #+#             */
/*   Updated: 2024/11/25 17:06:32 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// if one is not command, get the last inde
/* int	is_command()
{

}
 */
void handle_commands(t_tokens *tokens, t_env *env, char **envp)
{
	int	 execve_return;
	char **str;

	str[0] = "pwd";
	str[1] = 0;
	env->path = getenv("PWD");
	execve_return = execve(env->path, str, envp);
	if(env->path == NULL)
		return ;
	ft_printf("%d : %s\n", execve_return, tokens->token);
	//printf("%s\n", env->path);
}

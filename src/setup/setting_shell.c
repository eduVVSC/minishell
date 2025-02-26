/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvieira <edvieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 17:50:39 by edvieira          #+#    #+#             */
/*   Updated: 2025/02/26 14:20:09 by edvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Will uptade the SHLVL value, and
/// @brief if there is no value, it will start it to 1
/// @param env
void	update_shell_lvl(t_env *env)
{
	t_env	*tmp;
	int		new_value;

	new_value = 1;
	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->var_name, "SHLVL") == 0)
		{
			if (tmp->var_value != NULL)
				new_value = ft_atoi(tmp->var_value) + 1;
			break ;
		}
		tmp = tmp->next;
	}
	if (tmp && tmp->var_value)
	{
		free (tmp->var_value);
		tmp->var_value = ft_itoa(new_value);
	}
}

/// @brief Check if there is shlvl in the env list
/// @brief and add it if it doesn't
/// @param env
void	check_shellvl(t_env *env)
{
	t_env	*tmp;
	t_env	*shlvl;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->var_name, "SHLVL") == 0)
			return ;
		tmp = tmp->next;
	}
	shlvl = creating_env_var("SHLVL=1");
	adding_var_in_list(&env, shlvl);
}

/// @brief Set the shell list for the program to start
/// @param envp
/// @return (shell)
t_shell	*setting_shell(int ac, char **av, char **envp)
{
	t_shell	*shell;

	(void) ac;
	(void) av;
	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->tree = NULL;
	shell->tokens = NULL;
	shell->cmd_list = NULL;
	shell->heredock = NULL;
	shell->dir_now = ft_strjoin_free_s1(getcwd(NULL, 0), "$ ");
	create_env(shell, envp);
	update_shell_lvl(shell->env);
	check_shellvl(shell->env);
	return (shell);
}

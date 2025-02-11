/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvieira <edvieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:37:08 by edvieira          #+#    #+#             */
/*   Updated: 2025/02/11 15:38:13 by edvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Create the ? variable in the env list!
/// @return (node - success) (NULL - malloc error)
t_env	*creating_exit_code_var(void)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->var_name = ft_strdup("?");
	new_node->operant = NULL;
	new_node->var_value = ft_strdup("0");
	new_node->next = NULL;
	new_node->behaviour = 0;
	new_node->printed = 0;
	return (new_node);
}

/// @brief Create the enviroment when envp is null
/// @return (Head node - success) (NULL - malloc error)
t_env	*create_env_no_envp(void)
{
	t_env	*env;

	env = NULL;
	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env = creating_exit_code_var();
	env->next = creating_env_var("PWD=");
	env->next->var_value = getcwd(NULL, 0);
	env->next->next = creating_env_var("SHLVL=");
	env->next->next->next = creating_env_var_w_no_value("OLDPWD");
	return (env);
}

/// @brief create the enviroment with the envp inputs
/// @param envp
/// @return (Head node - success) (NULL - malloc error)
t_env	*create_env_envp(char **envp)
{
	t_env	*env_head;
	t_env	*tmp;
	int		i;

	i = 0;
	env_head = creating_exit_code_var();
	if (!env_head)
		return (NULL);
	tmp = env_head;
	while (envp[i] != NULL)
	{
		tmp->next = creating_env_var(envp[i]);
		if (tmp->next != NULL)
			tmp = tmp->next;
		i++;
	}
	tmp->next = NULL;
	return (env_head);
}

/// @brief create the enviroment with the envp inputs
/// @param envp
/// @return (Head node - success) (NULL - malloc error)
void	*create_env(t_shell *shell, char **envp)
{
	if (envp[0])
		shell->env = create_env_envp(envp);
	else
		shell->env = create_env_no_envp();
	if (!shell->env)
		clean_and_terminate(shell);
}

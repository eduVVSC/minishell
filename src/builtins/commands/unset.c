/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:44:39 by dioferre          #+#    #+#             */
/*   Updated: 2024/11/29 14:52:16 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Remove the variable from the env list
/// @param env
/// @param env_to_remove
/// @return (0 node removed) (1 node is not in the list)
int	remove_env_var(t_env *env, char *env_to_remove)
{
	t_env	*tmp;

	env = env->next;
	while (env->next)
	{
		if (ft_strcmp(env_to_remove, env->next->var_name) == 0)
		{
			tmp = env->next;
			env->next = env->next->next;
			free_env_node(tmp);
			return (0);
		}
		env = env->next;
	}
	return (1);
}

/// @brief Free the memory allocated to the node strings and set them to NULL
/// @param node
void	clean_first_node(t_env *node)
{
	free(node->var_name);
	if (node->operant)
		free(node->operant);
	if (node->var_value)
		free(node->var_value);
	node->var_name = NULL;
	node->operant = NULL;
	node->var_value = NULL;
}

/// @brief Free the node attributes and set
/// @brief /// @briefthem to NULL(var_name, operant, var_value)
/// @param node
void	clean_env_node_attributes(t_env *node)
{
	free(node->var_name);
	free(node->operant);
	free(node->var_value);
	node->var_name = NULL;
	node->operant = NULL;
	node->var_value = NULL;
}

/// @brief handle the removal of the head node
/// @param env
/// @return (0 success) (1 empty env)
int	on_first_node(t_env **env)
{
	t_env	*next_node;

	if (!env)
		return (1);
	next_node = (*env)->next;
	if (!next_node)
	{
		clean_first_node(*env);
		return (0);
	}
	clean_env_node_attributes(*env);
	(*env)->var_name = ft_strdup(next_node->var_name);
	if (next_node->operant)
		(*env)->operant = ft_strdup(next_node->operant);
	else
		(*env)->operant = NULL;
	if (next_node->var_value)
		(*env)->var_value = ft_strdup(next_node->var_value);
	else
		(*env)->var_value = NULL;
	(*env)->next = next_node->next;
	free_env_node(next_node);
	return (0);
}

/// @brief Do the unset function without optionals
/// @param env
/// @param command
/// @return (0 success) (2 error)
int	do_unset(t_env *env, char **command)
{
	int	i;

	i = 0;
	if (check_exist_optionals(command) == -1)
		return (2);
	while (command[++i])
	{
		if (ft_strcmp(command[i], "?") != 0)
		{
			if (search_in_env(env, command[i]) == 0)
				remove_env_var(env, command[i]);
		}
	}
	return (0);
}

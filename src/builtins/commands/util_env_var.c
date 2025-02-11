/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_env_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvieira <edvieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:12:22 by edvieira          #+#    #+#             */
/*   Updated: 2025/02/11 15:16:38 by edvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Create a complete enviroment variable(name+operant+value)
/// @param full_declaration
/// @return (t_env var -> succes)(NULL -> malloc error)
t_env	*creating_env_var(char *full_declaration)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->var_name = only_name(full_declaration);
	new_node->operant = only_operant(full_declaration);
	new_node->var_value = only_value(full_declaration);
	new_node->next = NULL;
	new_node->printed = 0;
	if (check_var_name(new_node->var_name) == 1)
	{
		free_env_node(new_node);
		return (NULL);
	}
	if (new_node->operant[0] == '=')
		new_node->behaviour = 0;
	else
		new_node->behaviour = 1;
	return (new_node);
}

/// @brief Create a  enviroment variable without value nor operant(name)
/// @param full_declaration
/// @return (t_env var -> succes) (NULL -> malloc error)
t_env	*creating_env_var_w_no_value(char *full_declaration)
{
	t_env	*new_node;

	if (check_var_name(full_declaration) == 1)
		return (NULL);
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->var_name = ft_strdup(full_declaration);
	new_node->operant = NULL;
	new_node->var_value = NULL;
	new_node->next = NULL;
	new_node->behaviour = 0;
	new_node->printed = 0;
	return (new_node);
}

/// @brief create a new variable, with or without values in it
/// @param declaration string with full declaration of new variable
/// @return created_node
t_env	*creating_var(char *declaration)
{
	if (check_if_have_equal_sign(declaration) != -1)
		return (creating_env_var(declaration));
	return (creating_env_var_w_no_value(declaration));
}

/// @brief Search for the given variable name in the env list
/// @param env
/// @param searching_var
/// @return (0 found) (1 not found)
int	search_in_env(t_env *env, char *searching_var)
{
	while (env != NULL)
	{
		if (ft_strcmp(env->var_name, searching_var) == 0)
			return (0);
		env = env->next;
	}
	return (1);
}

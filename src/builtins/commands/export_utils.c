/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvieira <edvieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:43:41 by edvieira          #+#    #+#             */
/*   Updated: 2025/02/11 15:13:27 by edvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Print one node in the export format "declare -x [var]"
/// @param node
void	print_env_export(t_env *node)
{
	ft_printf("declare -x ");
	ft_printf("%s", node->var_name);
	if (node->operant != NULL)
	{
		ft_printf("%s", node->operant);
		ft_printf("\"%s\"", node->var_value);
	}
	ft_printf("\n");
}

/// @brief Count how many nodes are in the env list
/// @param env
/// @return many_nodes
int	count_env(t_env *env)
{
	int	i;

	i = 0;
	if (!env || env->var_name == NULL)
		return (0);
	while (env)
	{
		env = env->next;
		i++;
	}
	return (i);
}

/// @brief Zero all the printed values of the env nodes
void	zero_all_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		tmp->printed = 0;
		tmp = tmp->next;
	}
}

/// @brief Will add the new_variable in the list whenever
/// @brief they found one string that is "lower" than this one
/// @param env
/// @param new_var
void	add_new_variable(t_env *env, t_env *new_var)
{
	t_env	*tmp;
	t_env	*replaced_node;

	tmp = env;
	if (new_var->behaviour == 1)
	{
		new_var->behaviour = 0;
		free(new_var->operant);
		new_var->operant = ft_strdup("=");
	}
	while (ft_strcmp(tmp->var_name, new_var->var_name) < 0 && tmp->next != NULL)
		tmp = tmp->next;
	replaced_node = tmp->next;
	tmp->next = new_var;
	new_var->next = replaced_node;
}

/// @brief Will search for the variable in env and refresh it's value.
/// @param env
/// @param new_value
/// @param behaviour (define if its will add(1) or replace (0))
void	refresh_var_value(t_env *env, t_env *new_value, int behavior)
{
	if (new_value->var_value == NULL)
		return (free_env_node(new_value));
	while (ft_strcmp(env->var_name, new_value->var_name) != 0 && env != NULL)
		env = env->next;
	if (env == NULL)
		return ;
	if ((!env->operant || env->operant == 0) && new_value->operant != 0)
		env->operant = ft_strdup("=");
	if (behavior == 0 || !env->var_value)
	{
		free(env->var_value);
		env->var_value = ft_strdup(new_value->var_value);
	}
	else if (behavior == 1)
	{
		env->var_value = ft_strjoin_free_s1(env->var_value,
				new_value->var_value);
	}
	free_env_node(new_value);
}

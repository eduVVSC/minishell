/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:57:13 by edvieira          #+#    #+#             */
/*   Updated: 2025/02/25 10:41:07 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief deliver the error message and set the exit code(1)
/// @return (1)
int	handle_export_error(char *bad_export)
{
	char	*message;

	message = ft_strjoin("bash: export: '", bad_export);
	message = ft_strjoin_free_s1(message, "': not a valid identifier\n");
	ft_putstr_fd(message, 2);
	free (message);
	return (1);
}

/// @brief add the new variable to the list,
/// @brief if the already exist it will refresh it's value.
/// @param env list of enviroment var
/// @param node var to add/refresh in the env list
void	adding_var_in_list(t_env **env, t_env *node)
{
	if (!((*env)->var_name) || ((*env)->var_name) == NULL)
	{
		*env = node;
		node->next = NULL;
	}
	else if (search_in_env(*env, node->var_name) == 0)
		refresh_var_value(*env, node, node->behaviour);
	else
		add_new_variable(*env, node);
}

/// @brief print env variables sorted
void	print_sorted(t_env *env)
{
	t_env	*tmp;
	t_env	*lowest_node;
	int		many_prints;
	int		i;

	i = 0;
	many_prints = count_env(env);
	while (++i < many_prints)
	{
		tmp = env->next;
		lowest_node = tmp;
		while (tmp)
		{
			if (tmp->printed == 0)
			{
				if (lowest_node->printed == 1 && tmp->printed == 0)
					lowest_node = tmp;
				if (ft_strcmp(lowest_node->var_name, tmp->var_name) > 0)
					lowest_node = tmp;
			}
			tmp = tmp->next;
		}
		lowest_node->printed = 1;
		print_env_export(lowest_node);
	}
}

/// @brief do the export function
/// @return (0) succes (1) error
int	do_export(t_env **env, char **command)
{
	t_env	*node;
	int		exit_code;
	int		i;

	i = 0;
	exit_code = 0;
	while (command[++i] != NULL)
	{
		node = creating_var(command[i]);
		if (node == NULL && exit_code == 0)
			exit_code = handle_export_error(command[i]);
		else
			adding_var_in_list(env, node);
	}
	if (i == 1)
	{
		if (*env || *env != NULL)
			print_sorted(*env);
	}
	zero_all_env(*env);
	return (exit_code);
}

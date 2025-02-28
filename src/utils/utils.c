/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:47:47 by edvieira          #+#    #+#             */
/*   Updated: 2025/02/28 11:56:44 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Count how many nodes in env
/// @param env
/// @return (height)
int	env_height(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		env = env->next;
		i++;
	}
	return (i);
}

/// @brief Close fd[read & write]
/// @param fd
void	close_fds(int *fd)
{
	close (fd[READ]);
	close (fd[WRITE]);
}

/// @brief Will take the linked list env, and trasnfrom it
/// @brief to array
/// @param env
/// @return (**envp -> success) (NULL -> malloc error)
char	**transfrom_env_to_array(t_env *env)
{
	char	**envp;
	int		height;
	int		i;

	i = 0;
	height = env_height(env);
	envp = malloc(sizeof(char **) * (height + 1));
	if (!envp)
		return (NULL);
	while (env)
	{
		envp[i] = ft_strdup(env->var_name);
		if (env->operant)
		{
			envp[i] = ft_strjoin_free_s1(envp[i], env->operant);
			if (env->var_name)
				envp[i] = ft_strjoin_free_s1(envp[i], env->var_value);
		}
		env = env->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

void	free_n_add_exit_status(t_shell *shell, char *new_value)
{
	free(shell->env->var_value);
	shell->env->var_value = ft_strdup(new_value);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expansions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvieira <edvieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:21:27 by edvieira          #+#    #+#             */
/*   Updated: 2025/02/26 14:15:09 by edvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Separate the name of a variable defined
/// @brief in a string
/// @param str
/// @param start
/// @return (success - the var name)
char	*var_name(char *str, int start)
{
	char	*var_name;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	if (str[start + 1] == '?' || str[start] == '?')
		return (ft_strdup("?"));
	while ((str[start + i] >= 'a' && str[start + i] <= 'z')
		|| (str[start + i] >= 'A' && str[start + i] <= 'Z'))
		i++;
	var_name = malloc(sizeof(char) * (i + 1));
	i = 0;
	while ((str[start + i] >= 'a' && str[start + i] <= 'z')
		|| (str[start + i] >= 'A' && str[start + i] <= 'Z'))
	{
		var_name[i] = str[start + i];
		i++;
	}
	var_name[i] = 0;
	return (var_name);
}

static int	is_in_quotes(char *str, int char_position)
{
	int	i;
	int	close_quote;

	i = 0;
	close_quote = 0;
	while (i < char_position)
	{
		if (str[i] == '\"')
		{
			close_quote = handle_quotes(str, i, str[i]);
			if (close_quote > char_position)
				return (1);
		}
		i++;
	}
	return (0);
}

// Function will search for the $ and Returns its (index)
// 0->general(no quote) 1(single) 2(dob)
int	check_expand(char *str)
{
	int	i;
	int	state;

	i = -1;
	state = GENERAL;
	while (str[++i])
	{
		set_quote_state(str[i], &state);
		if ((str[i] == '$' && state % 2 == 0)
			&& (ft_isalnum(str[i + 1]) || str[i + 1] == '?'))
			return (i);
	}
	return (-1);
}

// Search for the variable in the env,
// If found, return its (value), if it don't, return (NULL)
char	*get_env_var_value(t_env *env, char *var_searching)
{
	while (env != NULL && ft_strcmp(env->var_name, var_searching) != 0)
		env = env->next;
	if (!env)
		return (NULL);
	return (env->var_value);
}

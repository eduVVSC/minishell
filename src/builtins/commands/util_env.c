/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:44:39 by dioferre          #+#    #+#             */
/*   Updated: 2025/02/28 11:54:46 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Separate the name from the hole declaration
/// @param str
/// @return variable name
char	*only_name(char *str)
{
	char	*name;
	int		i;

	i = 0;
	name = malloc(sizeof(char) * 1);
	if (!name)
		return (NULL);
	name[0] = 0;
	while (str[i] != '=' && str[i] != '+')
	{
		name = join_str_char(name, str[i]);
		i++;
	}
	return (name);
}

/// @brief Separate the value from the hole declaration
/// @param str
/// @return variable value
char	*only_value(char *str)
{
	char	*var_value;
	int		i;

	i = 0;
	var_value = malloc(sizeof(char) * 1);
	if (!var_value)
		return (NULL);
	var_value[0] = 0;
	while (str[i] != '=')
		i++;
	while (str[++i] != '\0')
		var_value = join_str_char(var_value, str[i]);
	return (var_value);
}

/// @brief Separate the operant from the hole declaration
/// @param str
/// @return variable operant
char	*only_operant(char *str)
{
	char	*operand;
	int		i;

	i = 0;
	while (str[i] != '=')
		i++;
	if (str[i - 1] == '+')
		operand = ft_strdup("+=");
	else
		operand = ft_strdup("=");
	return (operand);
}

/// @brief Checking if the given name is acceptable
/// @param var_name
/// @return (0 acceptable name) (1 wrong name)
int	check_var_name(char *var_name)
{
	int	i;

	i = 0;
	if (!((var_name[i] >= 'a' && var_name[i] <= 'z')
			|| (var_name[i] >= 'A' && var_name[i] <= 'Z')))
		return (1);
	while (var_name[++i])
		if (!((var_name[i] >= 'a' && var_name[i] <= 'z')
				|| (var_name[i] >= 'A' && var_name[i] <= 'Z')
				|| var_name[i] == '_'
				|| (var_name[i] >= '0' && var_name[i] <= '9')))
			return (1);
	return (0);
}

/// @brief Check if the variable declaration has a equal sign
/// @param declaration
/// @return ('=' index when found) (-1 when not found)
int	check_if_have_equal_sign(char *declaration)
{
	int	i;

	i = 0;
	while (declaration[++i] != '\0')
		if (declaration[i] == '=')
			return (i);
	return (-1);
}

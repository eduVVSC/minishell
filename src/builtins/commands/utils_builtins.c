/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvieira <edvieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:44:39 by dioferre          #+#    #+#             */
/*   Updated: 2025/03/01 13:28:24 by edvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Check if are any optionals in the command
/// @param command
/// @return (command array hight) (-1 no optionals)
int	check_exist_optionals(char **command)
{
	int	i;

	i = 0;
	while (command[i])
	{
		if (command[i][0] == '-')
			return (-1);
		i++;
	}
	return (i);
}

/// @brief joins a strinf with a character
/// @param s1
/// @param charac
/// @return (joined string)
char	*join_str_char(char *s1, char charac)
{
	char	*str;
	int		i;

	i = -1;
	str = malloc((ft_strlen(s1) + 2) * sizeof(char));
	if (!str)
		return (NULL);
	while (s1[++i] != '\0')
		str[i] = s1[i];
	str[i] = charac;
	i++;
	str[i] = '\0';
	free(s1);
	return (str);
}

/// @brief Will compare the string characters
/// @brief  until they are different or both string ended
/// @param str1
/// @param str2
/// @return (0 equal) (!0 if they are different)
int	ft_strcmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] != '\0' || str2[i] != '\0')
	{
		if (str1[i] != str2[i])
			return ((unsigned char) str1[i] - (unsigned char) str2[i]);
		i++;
	}
	return (0);
}

/// @brief Join s1 and s2 and free the s1 memory
/// @param str1
/// @param str2
/// @return (Joined string)
char	*ft_strjoin_free_s1(char *str1, char *str2)
{
	char	*str;
	int		count;
	int		count2;
	int		len;

	count = 0;
	len = (ft_strlen(str1) + ft_strlen(str2));
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (count < len && str1[count] != '\0')
	{
		str[count] = str1[count];
		count++;
	}
	count2 = 0;
	while (count < len && str2[count2] != '\0')
	{
		str[count] = str2[count2];
		count++;
		count2++;
	}
	free(str1);
	str[count] = '\0';
	return (str);
}

/// @brief Count the height of and bidimensional array
/// @param array
/// @return (array_height)
int	get_height(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return (-1);
	while (array[i])
		i++;
	return (i);
}

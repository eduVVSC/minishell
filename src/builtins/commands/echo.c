/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvieira <edvieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:48:28 by dioferre          #+#    #+#             */
/*   Updated: 2025/02/03 10:21:39 by edvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Check the type of dependency of the command
/// @return (0 is an -n) (1 is not -n)
int	check_type(char *dependency)
{
	int	i;

	i = 1;
	if (dependency[0] != '-')
		return (0);
	while (dependency[i] != '\0')
	{
		if (dependency[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

/// @brief check the dependencies accept (-n or -nnnnnn), if there is "-n" it will disable the \n
/// @return (0 has new_line) (1 no new_line)
int	checking_dependecies(char **cmd)
{
	int	i;
	int	value_returned;
	int	what_to_do;

	i = 0;
	what_to_do = 0;
	value_returned = 1;
	while (cmd[++i] != NULL && value_returned == 1)
	{
		value_returned = check_type(cmd[i]);
		if (value_returned == -1)
			return (-1);
		if(value_returned == 1)
		{
			what_to_do = value_returned;
		}
	}
	return (what_to_do);
}

/// @brief Print all the command arguments
// BREAKS WHEN YOU DO "echo -n" without any argument :^)
void	printing(char **command, int new_line_flag)
{
	int	i;

	i = 1;
	while (check_type(command[i]) == 1)
		i++;
	while (command[i])
	{
		ft_printf("%s", command[i]);
		if(command[i + 1] != NULL)
			ft_printf(" ");
		i++;
	}
	if (new_line_flag == 0)
		ft_printf("\n");
}

/// @brief do the echo function
/// @return (0 succes) (1 error)
int	do_echo(char **command)
{
	int	new_line_flag;

	new_line_flag = 0;
	if (command[1] == NULL) // echo whithout argumments
		ft_printf("\n");
	else
	{
		if (checking_dependecies(command) == 1) // no new line
			new_line_flag = 1;
		printing(command, new_line_flag);
	}
	return (0);
}

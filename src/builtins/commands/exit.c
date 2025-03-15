/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvieira <edvieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:42:43 by edvieira          #+#    #+#             */
/*   Updated: 2025/03/15 20:15:35 by edvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_only_nrs(char *arg)
{
	int	i;

	i = 0;
	if (!arg)
		return (0);
	while (arg[i])
	{
		if (!ft_isdigit(arg[i])
			&& (arg[i] != '-' && arg[i] != '+'))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(arg, 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			return (2);
		}
		i++;
	}
	return (0);
}

int	get_exit_code(char **cmd)
{
	unsigned char	exit_code;

	if (cmd[1])
		exit_code = ((unsigned char) ft_atoi(cmd[1]));
	else
		exit_code = 0;
	if (has_only_nrs(cmd[1]) == 2)
		return (2);
	else if (get_matrix_len(cmd) > 2)
	{
		printf("exit\n");
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd("too many arguments\n", 2);
		return (-1);
	}
	printf("exit\n");
	return (exit_code);
}

void	do_exit(t_shell *shell, char **cmd)
{
	int	exit_code;

	exit_code = get_exit_code(cmd);
	if (exit_code < 0)
		exit_code = exit_code * -1;
	ft_free_double_arr(&cmd);
	clean_and_terminate_with_status(shell, exit_code);
}

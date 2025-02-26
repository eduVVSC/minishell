/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvieira <edvieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:36:20 by dioferre          #+#    #+#             */
/*   Updated: 2025/02/26 14:17:06 by edvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	search_exp_heredoc(char *str)
{
	int	i;
	int	state;

	i = -1;
	state = 0;
	while (str[++i])
	{
		if ((str[i] == '$' && state % 2 == 0)
			&& (ft_isalnum(str[i + 1]) || str[i + 1] == '?'))
			return (i);
	}
	return (-1);
}

char	*expand_heredoc(t_env *env, char *str)
{
	int		flag;
	char	*var;
	char	*var_value;

	flag = 0;
	var = NULL;
	while (flag != -1)
	{
		flag = search_exp_heredoc(str);
		if (flag != -1)
		{
			var = var_name(str, (flag + 1));
			var_value = get_env_var_value(env, var);
			if (var_value == NULL)
				var_value = "";
			str = re_wrinting_string(str, var_value, flag,
					(ft_strlen(var) + 1));
			free(var);
		}
	}
	return (str);
}

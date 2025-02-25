/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expansions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvieira <edvieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:19:35 by edvieira          #+#    #+#             */
/*   Updated: 2025/02/25 14:21:18 by edvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Will rewrite the string adding the variable expended value to it
/// @param str
/// @param expand_value
/// @param where_to_change
/// @param var_len
/// @return (success - the rewritten string)
char	*re_wrinting_string(char *str, char *expand_value,
	int where_to_change, int var_len)
{
	char	*new_str;
	int		k;
	int		i;
	int		j;

	i = -1;
	j = -1;
	k = -1;
	new_str = malloc(sizeof(char) * (ft_strlen(str) - var_len + ft_strlen(expand_value) + 1));
	while (++i < where_to_change)
		new_str[i] = str[i];
	while (expand_value[++j] != 0)
		new_str[i + j] = expand_value[j];
	j = i + j;
	i++;
	if (str[i] == '?')
		i++;
	else
		while ((str[++i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= 'A' && str[i] <= 'Z'));
	while (str[i + (++k)] != '\0')
		new_str[j + k] = str[i + k];
	new_str[j + k] = '\0';
	free(str);
	return (new_str);
}

/// @brief Take of the quotes from the str
/// @param str
/// @return (success - return the no quoted string)
char	*takeoff_quotes(char *str)
{
	char	*new_str;
	int		strlen;
	int		i;

	i = 0;
	strlen = ft_strlen(str);
	new_str = malloc((strlen - 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	while (++i < (strlen - 1))
		new_str[i - 1] = str[i];
	new_str[i -1] = '\0';
	free(str);
	return (new_str);
}

/// @brief Function will search and do the expansions
/// @brief on the string(if they exist)
/// @param env
/// @param str
/// @return (success - will return the expanded string)
char	*handle_expension(t_env *env, char *str)
{
	int		flag;
	char	*var;
	char	*var_value;

	flag = 0;
	var = NULL;
	while (flag != -1)
	{
		flag = check_expand(str);
		if (flag != -1)
		{
			var = var_name(str, (flag + 1));
			var_value = get_env_var_value(env, var);
			if (var_value == NULL)
				var_value = "";
			str = re_wrinting_string(str, var_value, flag,
					(ft_strlen(var) + 1));
		}
	}
	free(var);
	return (str);
}

/// @brief Function checks the type of the token and expand if needed of wanted
/// @param env
/// @param token
void	expand_token(t_env *env, t_tokens *token)
{
	static int	heredoc_flag;

	if (!token->token)
		return ;
	if (token->type == HEREDOC)
		heredoc_flag = TRUE;
	else if (heredoc_flag == TRUE)
		heredoc_flag = FALSE;
	else
		token->token = handle_expension(env, token->token);
}

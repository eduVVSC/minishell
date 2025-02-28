/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:22:29 by edvieira          #+#    #+#             */
/*   Updated: 2025/02/28 09:24:10 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Give the heredoc error message
/// @return (1)
int	heredoc_error(void)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(" syntax error near unexpected token `newline'\n", 2);
	return (1);
}

/// @brief Count how many heredocs are in the tokens
/// @param tokens
/// @return (heredoc quantity)
int	count_heredocs(t_tokens *tokens)
{
	int	counter;

	counter = 0;
	if (!tokens)
		return (0);
	while (tokens)
	{
		if (tokens->type == HEREDOC)
			counter++;
		tokens = tokens->next;
	}
	return (counter);
}

t_heredock	*free_heredock(t_heredock *heredock)
{
	t_heredock	*tmp;

	while (heredock)
	{
		tmp = heredock->next;
		free (heredock->key);
		if (heredock->fullinput_until_key)
			free (heredock->fullinput_until_key);
		free(heredock);
		heredock = tmp;
	}
	return (NULL);
}

/// @brief Join both strings and add the '\n' in
/// @brief  end of the concatenated string, free s1
/// @param s1
/// @param s2
/// @return (conct string -> success) (NULL -> malloc error)
char	*ft_strjoin_w_new_line(char *s1, char *s2)
{
	char	*str;
	int		count;
	int		count2;
	int		len;

	count = 0;
	len = (ft_strlen(s1) + ft_strlen(s2));
	str = malloc((len + 2) * sizeof(char));
	if (!str)
		return (NULL);
	while (count < len && s1[count] != '\0')
	{
		str[count] = s1[count];
		count++;
	}
	count2 = 0;
	while (count < len && s2[count2] != '\0')
	{
		str[count] = s2[count2];
		count++;
		count2++;
	}
	str[count] = '\n';
	str[count + 1] = '\0';
	return (free(s1), str);
}

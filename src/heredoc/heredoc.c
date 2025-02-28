/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvieira <edvieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:25:43 by edvieira          #+#    #+#             */
/*   Updated: 2025/02/28 11:07:44 by edvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_eof_heredoc(char *key)
{
	ft_printf("warning: here-document ");
	ft_printf("delimited by end-of-file (wanted '%s')!\n", key);
}

/// @brief Do the heredoc of one key and concatenate the string to
/// @brief the desired location in the structure
/// @param heredock
/// @return (TRUE -> sigint interruption) (FALSE -> no signal caught)
int	doing_key(t_heredock *heredock)
{
	char	*input;

	input = NULL;
	heredock->fullinput_until_key = ft_strdup("");
	while (1)
	{
		input = readline("> ");
		if (g_sig_sign == SIGINT)
		{
			if (input)
				free (input);
			return (TRUE);
		}
		if (!input || ft_strcmp(input, heredock->key) == 0)
		{
			if (!input)
				print_eof_heredoc(heredock->key);
			return (FALSE);
		}
		else
			heredock->fullinput_until_key = ft_strjoin_w_new_line
				(heredock->fullinput_until_key, input);
	}
	return (FALSE);
}

// change it to return an error code (1), if heredoc couldnt finish

/// @brief Will send the heredoc to be done, than it will expand the
/// @brief  written heredoc and send it to the fd
/// @param shell
/// @param heredock
/// @param fd
void	doing_heredock(t_shell *shell, t_heredock *heredock, int fd)
{
	int	heredoc_fd;

	if (doing_key(heredock))
	{
		free_heredock(heredock);
		return ;
	}
	if (heredock->state != SINGLE_QUO)
		heredock->fullinput_until_key
			= expand_heredoc(shell->env, heredock->fullinput_until_key);
	if (ft_strlen(heredock->fullinput_until_key) > 1000000)
	{
		free_heredock(heredock);
		pipe_error(shell);
		return ;
	}
	ft_putstr_fd(heredock->fullinput_until_key, fd);
	free_heredock(heredock);
}

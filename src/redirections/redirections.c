/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 11:35:50 by dioferre          #+#    #+#             */
/*   Updated: 2025/02/10 11:08:55 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
On infile redirections bash only uses the last redirection.
On outfile it does it to all the redirections.
*/

void	file_error(t_shell *shell) // Need to do this properly lol
{
	printf("infile or outfile error!\n");
	clean_and_terminate_with_status(shell, 1);
}

void	handle_infile(t_shell *shell, t_tokens *tokens)
{
	char	*file_name;
	int		fd;

	if (tokens->next)
		file_name = tokens->next->token;
	if (!file_name)
		file_error(shell);
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		file_error(shell);
	dup_from_input(fd);
}

void	handle_outfile(t_shell *shell, t_tokens *tokens)
{
	char	*file_name;
	int fd;

	if (tokens->next)
		file_name = tokens->next->token;
	if (!file_name)
		file_error(shell);
	if (tokens->type == APP_OUTFILE)
	{
		fd = open(file_name, O_RDWR | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
			file_error(shell);
	}
	else if (tokens->type == TRU_OUTFILE)
	{
		fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			file_error(shell);
	}
	dup_to_output(fd);
}

void	handle_redirections(t_shell *shell, t_tokens *tokens, int last_heredoc_fd)
{
	while (tokens)
	{
		if (tokens->state == GENERAL)
		{
			if (tokens->type == INFILE)
				handle_infile(shell, tokens); // cat < infile1 < infile2 < infile3
			else if (tokens->type == HEREDOC)
				dup2(last_heredoc_fd, STDIN_FILENO);
			else if (tokens->type == TRU_OUTFILE || tokens->type == APP_OUTFILE)
				handle_outfile(shell, tokens);
		}
		tokens = tokens->next;
	}
}

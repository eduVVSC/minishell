/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvieira <edvieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 11:35:50 by dioferre          #+#    #+#             */
/*   Updated: 2025/02/26 14:19:39 by edvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
On infile redirections bash only uses the last redirection.
On outfile it does it to all the redirections.
*/

void	file_error(char *file_name, t_shell *shell, int redirection_type)
{
	struct stat	path_stat;

	ft_putstr_fd("minishell: ", 2);
	if (file_name)
		ft_putstr_fd(file_name, 2);
	if (stat(file_name, &path_stat) == -1)
		ft_putstr_fd(": No such file or directory\n", 2);
	else if ((access(file_name, R_OK) == -1 && redirection_type == READ)
		|| (access(file_name, W_OK) == -1 && redirection_type == WRITE))
		ft_putstr_fd(": Permission denied\n", 2);
	else
		ft_putstr_fd(": Something went wrong.\n", 2);
	clean_and_terminate_with_status(shell, 1);
}

void	print_ambiguous_redirection(t_shell *shell)
{
	ft_putstr_fd("minishell: ambiguous redirect.\n", 2);
	clean_and_terminate_with_status(shell, 1);
}

void	handle_infile(t_shell *shell, t_tokens *tokens)
{
	char	*file_name;
	int		fd;

	if (tokens->next)
		file_name = tokens->next->token;
	else
		print_ambiguous_redirection(shell);
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		file_error(file_name, shell, READ);
	dup_from_input(fd);
}

void	handle_outfile(t_shell *shell, t_tokens *tokens)
{
	char	*file_name;
	int		fd;

	if (tokens->next)
		file_name = tokens->next->token;
	else
		print_ambiguous_redirection(shell);
	if (tokens->type == APP_OUTFILE)
	{
		fd = open(file_name, O_RDWR | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
			file_error(file_name, shell, WRITE);
	}
	else if (tokens->type == TRU_OUTFILE)
	{
		fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			file_error(file_name, shell, WRITE);
	}
	dup_to_output(fd);
}

void	handle_redirections(t_shell *shell,
		t_tokens *tokens, int last_heredoc_fd)
{
	while (tokens)
	{
		if (tokens->state == GENERAL)
		{
			if (tokens->type == INFILE)
				handle_infile(shell, tokens);
			else if (tokens->type == HEREDOC)
				dup2(last_heredoc_fd, STDIN_FILENO);
			else if (tokens->type == TRU_OUTFILE || tokens->type == APP_OUTFILE)
				handle_outfile(shell, tokens);
		}
		tokens = tokens->next;
	}
}

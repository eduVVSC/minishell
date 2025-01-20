/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 11:35:50 by dioferre          #+#    #+#             */
/*   Updated: 2025/01/12 18:16:09 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*

On infile redirections bash only uses the last redirection.
On outfile it does it to all the redirections.

*/
/*
void	file_error(void) // Need to do this properly lol
{
	printf("infile or outfile error!");
	exit (0);
}

void	handle_infile(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		file_error();
	dup_from_input(fd);
}
void	handle_outfile(char *redir_type, char *file_name)
{
	int fd;

	if (!strcmp(redir_type, ">"))
	{
		fd = open(file_name, O_RDWR | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
			file_error();
	}
	else if (!strcmp(redir_type, ">>"))
	{
		fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			file_error();
	}
	dup_to_output(fd);
}

void	handle_normal_redir(t_shell *shell, t_tree_node *node)
{
	int	i;

	i = 0;
	while (node->content[i])
	{
		if (is_infile(node->content[i]))
			handle_infile(node->content[i + 1]);
		else if (is_outfile(node->content[i]))
			handle_outfile(node->content[i], node->content[i + 1]);
		i++;
	}
}
 */

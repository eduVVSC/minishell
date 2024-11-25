/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:14:53 by dioferre          #+#    #+#             */
/*   Updated: 2024/11/25 16:43:03 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token_type(int token_type)
{
	if (token_type == 0)
		ft_printf("   STRING   ");
	if (token_type == 1)
		ft_printf("    PIPE    ");
	if (token_type == 2)
		ft_printf("     &      ");
	if (token_type == 3)
		ft_printf("   INFILE   ");
	if (token_type == 4)
		ft_printf("   OUTFILE  ");
	if (token_type == 5)
		ft_printf("   HEREDOC  ");
	if (token_type == 6)
		ft_printf(" EXPANSION  ");
}

void	print_token_state(int token_state)
{
	if (token_state == 0)
		ft_printf("   GENERAL   ");
	if (token_state == 1)
		ft_printf("SINGLE QUOTE ");
	if (token_state == 2)
		ft_printf("DOUBLE QUOTE ");
	if (token_state == 3)
		ft_printf("  EXPANDED   ");
}

void	print_token_content(char *str)
{
	int	i = 0;
	int	len;
	int	spaces;

	len = ft_strlen(str);
	spaces = 13 - len;
	while (i < (spaces / 2) + (spaces % 2))
	{
		write(1, " ", 1);
		i++;
	}
	ft_putstr_fd(str, 1);
	while (i < spaces)
	{
		write(1, " ", 1);
		i++;
	}
}

void	print_individual_tkn(t_tokens *token)
{
	write(1, "|", 1);
	print_token_content(token->token);
	write(1, "|", 1);
	print_token_type(token->type);
	write(1, "|", 1);
	print_token_state(token->state);
	if (token->index >= 10)
		ft_printf("|      %d     |\n", token->index);
	else
		ft_printf("|      %d      |\n", token->index);
}


void	print_tokens(t_tokens *tokens)
{
	if (!tokens->token)
		return ;
	printf("+-------------+------------+-------------+-------------+\n");
	printf("|             |            |             |             |\n");
	printf("|    TOKEN    |    TYPE    |    STATE    |    INDEX    |\n");
	printf("|             |            |             |             |\n");
	printf("+-------------+------------+-------------+-------------+\n");
	while (tokens->next)
	{
		print_individual_tkn(tokens);
		tokens = tokens->next;
		if (tokens->next)
			printf("|-------------|------------|-------------|-------------|\n");
	}
	printf("|-------------|------------|-------------|-------------|\n");
	print_individual_tkn(tokens);
	printf("+-------------+------------+-------------+-------------+\n");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:14:53 by dioferre          #+#    #+#             */
/*   Updated: 2024/11/19 17:55:50 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token_type(int token_type)
{
	if (token_type == 0)
		printf("   COMMAND   ");
	if (token_type == 1)
		printf("     PIPE    ");
	if (token_type == 2)
		printf("    INFILE   ");
	if (token_type == 3)
		printf("   OUTFILE   ");
}

void	print_token_state(int token_state)
{
	if (token_state == 0)
		printf("   GENERAL   ");
	if (token_state == 1)
		printf(" SINGLE QUOTE");
	if (token_state == 2)
		printf(" DOUBLE QUOTE");
}

void	print_token_content(char *str)
{
	int	i = 0;
	int	len;
	int	spaces;

	len = ft_strlen(str);
	spaces = 13 - len;
	while (i <= (spaces / 2) + (spaces % 2))
		write(1, " ", 1);
	ft_putstr_fd(str, 1);
	while (i < spaces)
		write(1, " ", 1);
}

void	print_individual_tkn(t_tokens *token)
{
	printf("|");
	print_token_content(token->token);
	printf("|");
	print_token_type(token->type);
	printf("|");
	print_token_state(token->state);
	if (token->index >= 10)
		printf("|-----%d------|\n", token->index);
	else
		printf("|------%d------|\n", token->index);
}


void	print_tokens(t_tokens *tokens)
{
	printf("+-------------+------------+-------------+-------------+\n");
	printf("|             |            |             |             |\n");
	printf("|    TOKEN    |    TYPE    |    STATE    |    INDEX    |\n");
	printf("|             |            |             |             |\n");
	printf("+-------------+------------+-------------+-------------+\n");
	while (tokens->next != NULL)
	{
		print_individual_tkn(token);
		tokens = tokens->next;
		if (tokens->next)
			printf("|-------------|------------|-------------|-------------|\n");
	}
	printf("+-------------+------------+-------------+-------------+\n");
}

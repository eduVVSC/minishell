/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 15:00:21 by dioferre          #+#    #+#             */
/*   Updated: 2024/11/17 18:24:40 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"

// REMOVE AFTER MAKEFILE DONE LOLOLOL
int	word_count(char *str, char separator)
{
	int	i;
	int	words;

	i = 0;
	words = 1;
	if (!str || str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] == separator)
			words++;
		i++;
	}
	return (words);
}

// Creates, allocs and fills a string.
char	*fill_str(char *str, int target_word, char separator)
{
	char *cmd;
	int	i;
	int	j;
	int	word_now;
	int	strlen;

	i = 0;
	j = 0;
	strlen = 0;
	word_now = 1;
	while (str[i] && word_now < target_word) //change this to a fucking function idiot.
	{
		if (str[i] == separator)
			word_now++;
		i++;
	}
	if (target_word != 1)
		i++; // until here lol
	while(str[i + strlen] != separator && str[i + strlen] != '\0')
		strlen++;
	cmd = malloc((strlen + 1) * sizeof(char)); // needs protection.
	while (j < strlen)
	{
		cmd[j] = str[i + j];
		j++;
	}
	cmd[j] = '\0';
	return(cmd);
}

// Creates a node, allocs memory and sets everything in it to NULL;
t_tokens	*fill_node(void)
{
	t_tokens	*node;

	node = malloc(sizeof(t_tokens));
	if (!node)
		return (NULL);
	node->i = 0;
	node->cmd = NULL;
	node->args = NULL;
	node->next = NULL;
	return (node);
}

// Creates the tokens list xd
void	fill_tokens(t_tokens *tokens, int nr)
{
	t_tokens *tmp;

	tmp = tokens;
	int	i;

	i = 0;

	while (i < nr)
	{
		tmp->next = fill_node();
		if (!tmp->next)
			return (NULL); // Dont forget to clean everything when done :D
		tmp = tmp->next;
		i++;
	}
	free(tmp);
}

t_tokens	*get_tokens(char *input)
{
	t_tokens *tokens;
	int	current_word;
	int	words;

	current_word = 1;
	words = word_count(input, '|');
	printf("Nr of words: %d\n", words);
	tokens = fill_node();
	fill_tokens(tokens, words);
	while (current_word <= words)
	{
		tokens->cmd = fill_str(input, current_word, '|');
		printf("Token #%d: %s\n", current_word, tokens->cmd);
		tokens = tokens->next;
		current_word++;
	}
	tokens->next = NULL;
	return (tokens);
}

int	main(void)
{
	t_tokens *tokens;
	char *input = "echo ola | cat | ls";
	int	i = 0;
	tokens = get_tokens(input);
}

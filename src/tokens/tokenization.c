/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 15:00:21 by dioferre          #+#    #+#             */
/*   Updated: 2024/11/18 16:06:12 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Function finds where the intended string is
Return the index of where the string starts. */
int	command_Start(char *str, int target_word, char separator)
{
	int	word_now;
	int	i;

	i = 0;
	word_now = 1;
	while (str[i] && word_now < target_word) //change this to a fucking function idiot.
	{
		if (is_separator(str[i]))
			word_now++;
		i++;
	}
	if (target_word != 1)
		i++;
	return (i);
}

/* Fill str part2, populates the given str with chars.*/
void	populate_str(char *str, char *cmd, int strlen, int index_start)
{
	int	j;

	j = 0;
	while (j < strlen)
	{
		cmd[j] = str[index_start + j];
		j++;
	}
	cmd[j] = '\0';
}

// Creates, allocs and fills a string.
char	*fill_str(char *str, int target_word, char separator)
{
	char	*cmd;
	int		strlen;
	int		index_start;

	strlen = 0;
	index_start = command_Start(str, target_word, separator);
	while(!(is_separator(str[index_start + strlen]))
			&& str[index_start + strlen] != '\0')
		strlen++;
	cmd = malloc((strlen + 1) * sizeof(char));
	if (!cmd)
		return (NULL);
	populate_str(str, cmd, strlen, index_start);
	return(cmd);
}

// Creates a node, allocs memory and sets everything in it to NULL;
t_tokens	*fill_node(void)
{
	t_tokens	*node;

	node = malloc(sizeof(t_tokens));
	if (!node)
		return (NULL);
	node->token = NULL;
	node->index = -1;
	node->state = -1;
	node->type = -1;
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
			return ; // void function
		//return (NULL); // Dont forget to clean everything when done :D
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
	words = word_count(input);
	if (words == -1) // Happens if a quote is left open, shouldnt matter if we handle it on validation.
		return (NULL);
	printf("Nr of words: %d\n", words);
	tokens = fill_node();
	fill_tokens(tokens, words);
	while (current_word <= words)
	{
		tokens->token = fill_str(input, current_word);
		tokens->index = current_word - 1;
		tokens = tokens->next;
		current_word++;
	}
	tokens->next = NULL;
	return (tokens);
}

int	main(void)
{
	t_tokens *tokens;
	char *input = "echo ola | cat | ls | echo 'ola | 12345'";
	int	i = 0;
	tokens = get_tokens(input);
	print_tokens(tokens);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 15:00:21 by dioferre          #+#    #+#             */
/*   Updated: 2024/11/25 16:40:03 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Function finds where the intended string is
Return the index of where the string starts. */
int	command_start(char *str, int target_word, char separator)
{
	int	word_now;
	int	i;

	i = 0;
	word_now = 0;
	while (is_separator(str[i]))
		i++;
	while (str[i] && word_now < target_word)
	{
		if (!is_separator(str[i]))
		{
			word_now++;
			if (word_now == target_word)
				return (i);
			if (str[i] == '\'' || str[i] == '\"')
				i = handle_quotes(str, i, str[i]) + 1;
			else
				while (!is_separator(str[i]) && str[i])
					i++;
		}
		else
			i++;
	}
	return (i);
}

/* Fill str part2, populates the given str with chars.*/
void	populate_str(char *str, char *cmd, int end, int start)
{
	int	i;

	i = 0;
	while (start + i <= end)
	{
		cmd[i] = str[start + i];
		i++;
	}
	cmd[i] = '\0';
}

// Creates, allocs and fills a string.
char	*fill_str(char *str, int target_word, char separator)
{
	char	*cmd;
	char	tmp;
	int		start;
	int		end;

	start = command_start(str, target_word, separator);
	end = start;
	if (str[start] == '\'' || str[start] == '\"')
		end = handle_quotes(str, start, str[start]);
	else
	{
		while (!(is_separator(str[end + 1]))
			&& str[end + 1])
			end++;
	}
	cmd = malloc((end - start + 2) * sizeof(char));
	if (!cmd)
		return (NULL);
	populate_str(str, cmd, end, start);
	return (cmd);
}

// Creates a node, allocs memory and sets everything in it to NULL;
static t_tokens	*fill_node(void)
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

// Creates the tokens list
static void	fill_tokens(t_tokens *tokens, int nr)
{
	t_tokens	*tmp;
	int			i;

	tmp = tokens;
	i = 1;
	while (i < nr)
	{
		tmp->next = fill_node();
		if (!tmp->next)
			return ; // void function
		tmp = tmp->next;
		i++;
	}
}

// Returns a linked list of tokens based on the given input.
t_tokens	*get_tokens(char *input)
{
	t_tokens	*tmp;
	t_tokens	*tokens;
	int			current_word;
	int			words;

	current_word = 1;
	words = word_count(input);
	if (!input)
		return (NULL);
	if (words == -1) // Happens if a quote is left open, shouldnt matter if we handle it on validation.
		return (NULL);
	tokens = fill_node();
	tmp = tokens;
	fill_tokens(tmp, words);
	while (current_word <= words)
	{
		tmp->token = fill_str(input, current_word, ' ');
		tmp->index = current_word - 1;
		tmp->state = get_token_state(tmp->token);
		tmp->type = get_token_type(tmp->token);
		tmp = tmp->next;
		current_word++;
	}
	tmp = NULL;
	return (tokens);
}

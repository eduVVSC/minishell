/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 15:00:21 by dioferre          #+#    #+#             */
/*   Updated: 2024/12/09 13:51:05 by dioferre         ###   ########.fr       */
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
	while (str[end + 1])
	{
		if (is_quote(str[end]))
			end = handle_quotes(str, end, str[end]);
		if (is_separator(str[end +1]))
			break;
		end++;
	}
	cmd = malloc((end - start + 2) * sizeof(char));
	if (!cmd)
		return (NULL);
	populate_str(str, cmd, end, start);
	return (cmd);
}

// Creates a node, allocs memory and sets everything in it to NULL;
static t_tokens	*fill_node(int index)
{
	t_tokens	*node;

	node = malloc(sizeof(t_tokens));
	if (!node)
		return (NULL);
	node->token = NULL;
	node->index = index;
	node->state = -1;
	node->type = -1;
	node->next = NULL;
	return (node);
}

// Creates the tokens list
static void	fill_tokens(t_tokens *tokens, char *input ,int words)
{
	t_tokens	*tmp;
	int			spaces;
	int			i;


	tmp = tokens;
	spaces = count_spaces(input);
	ft_printf("words: %d    spaces: %d\n", words, spaces);
	i = 1;
	while (i < words + spaces)
	{
		tmp->next = fill_node(i);
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
	if (!input)
		return (NULL);
	words = word_count(input);
	if (words == -1) // Happens if a quote is left open, shouldnt matter if we handle it on validation.
		return (NULL);
	tokens = fill_node(0);
	tmp = tokens;
	fill_tokens(tmp, input, words);
	while (current_word <= words)
	{
		tmp->token = fill_str(input, current_word, ' ');
		tmp->state = get_token_state(tmp->token);
		tmp->type = get_token_type(tmp->token);
		tmp->token = clean_tkn_quotes(tmp->token);
  		if (current_word < words) // if the current index is not pointing to the end of the input, it inserts a space token.
		{
			tmp = tmp->next;
			create_space_token(tmp);
		}
		tmp = tmp->next;
		current_word++;
	}
	tmp = NULL;
	return (tokens);
}

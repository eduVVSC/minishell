/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 15:00:21 by dioferre          #+#    #+#             */
/*   Updated: 2025/02/25 17:41:14 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Returns the len of the next token to be used when allocing memmory.
int	get_token_len(char *str)
{
	int	len;
	int	quote_state;

	len = 0;
	quote_state = GENERAL;
	while (str[len])
	{
		if (is_quote(str[len]))
			set_quote_state(str[len], &quote_state);
		else if (!quote_state
				&& (is_redir(str[len]) || str[len] == '|')) //checks if current char is a redir or pipe.
		{
			if (len == 0)
			{
				if (is_redir(str[1]))
					len++;
				len++;
			}
			break;
		}
		if (is_separator(str[len]) && quote_state == GENERAL)
			break;
		len++;
	}
	return (len);
}

// Creates, allocs and fills a string with the next token, also iterates through the given string.
char	*fill_str(char **str)
{
	char	*token;
	int		len;
	int		i;

	i = 0;
	while (is_separator(**str) == 1)
		*(*str)++;
	len = get_token_len((*str));
	token = malloc((len + 1) * sizeof(char));
	while (i < len)
	{
		token[i] = *(*str)++;
		i++;
	}
	token[i] = 0;
	return (token);
}

// Creates a node, allocs memory and sets everything in it to NULL;
static t_tokens	*create_node(void)
{
	t_tokens	*node;

	node = malloc(sizeof(t_tokens));
	if (!node)
		return (NULL);
	node->token = NULL;
	node->state = -1;
	node->index = 0;
	node->type = -1;
	node->next = NULL;
	return (node);
}

static void	create_and_link_node(char *input, t_tokens **node)
{
	t_tokens	*new_node;

	if ((*node)->token[0] == 0 && (*node)->state == EXPANDED)
	{
		free ((*node)->token);
		(*node)->token = NULL;
		(*node)->state = -1;
		(*node)->index = 0;
		(*node)->type = -1;
		(*node)->next = NULL;
	}
	else if (are_there_more_tokens(input))
	{
		new_node = create_node();
		(*node)->next = new_node;
		(*node) = (*node)->next;
	}
}

// Returns a linked list of tokens based on the given input.
t_tokens	*get_tokens(t_shell *shell ,char *input)
{
	t_tokens	*tmp;
	t_tokens	*head;

	if (!input)
		return (NULL);
	head = create_node();
	tmp = head;
	while (*input)
	{
		tmp->token = fill_str(&input);
			if (tmp->token[0] == 0)
				break;
		tmp->state = get_token_state(tmp->token);
		tmp->type = get_token_type(tmp->token);
		expand_token(shell->env, tmp);
		tmp->token = clean_tkn_quotes(tmp->token);
		create_and_link_node(input, &tmp); // Needs to enter here even if there are no more tokens ex: $EMPTY;
		if (!are_there_more_tokens(input))
			break ;
	}
	tmp = NULL;
	return (head);
}

/// token => (NULL)
/// token => ("")

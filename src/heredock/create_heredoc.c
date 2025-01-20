/*
#include "minishell.h"

/// @brief Create a heredoc node with everything set to NULL and the key given by read
/// @param key
/// @return (NULL -> malloc error) (node -> success)
t_heredock	*create_heredoc_node(char *key)
{
	t_heredock	*node;

	node = malloc(sizeof(t_heredock));
	if (!node)
		return (NULL);
	if (!key)
		node->key = NULL;
	else
		node->key = ft_strdup(key);
	node->fullinput_until_key = NULL;
	node->next = NULL;
	return (node);
}

/// @brief Create all the heredoc nodes after the head
/// @param command
/// @param i
/// @return (body_head -> if there is more heredocs) (NULL -> if there ain't no more heredocs)
t_heredock *create_heredoc_body(t_tree_node *node, int i)
{
	t_heredock	*body_head;
	t_heredock	*tmp;

	body_head = NULL;
	if (!node->content[i])
		return (NULL);
	while (node->content[i])
	{
		if (ft_strcmp(node->content[i], "<<") == 0)
		{
			if (!body_head)
			{
				body_head = create_heredoc_node(node->content[++i]);
				tmp = body_head;
			}
			else
			{
				tmp->next = create_heredoc_node(node->content[++i]);
				tmp = tmp->next;
			}
		}
		if (node->content[i])
			i++;
	}
	return (body_head);
}

/// @brief  Function take the command and create its heredoc list, with the needed keys in it node!
/// @param node
/// @return (heredoc_head)
t_heredock	*create_heredoc(t_tree_node *node)
{
	t_heredock	*head;
	int			i;

	i = 0;
	head = NULL;
	while (node->content[++i] != NULL)
	{
		if (ft_strcmp(node->content[i], "<<") == 0)
		{
			if (!node->content[++i])
				return (create_heredoc_node(NULL));
			else
				head = create_heredoc_node(node->content[i]);
			head->next = create_heredoc_body(node, (i + 1));
			break ;
		}
	}
	return (head);
}
 */

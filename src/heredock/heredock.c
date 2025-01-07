
#include "minishell.h"

int	heredoc_error()
{
	ft_putstr_fd("bash: syntax error near unexpected token `newline'", 2);
	return (1);
}

char	*ft_strjoin_w_new_line(char *s1, char *s2)
{
	char	*str;
	int		count;
	int		count2;
	int		len;

	count = 0;
	len = (ft_strlen(s1) + ft_strlen(s2));
	str = malloc((len + 2) * sizeof(char));
	if (!str)
		return (NULL);
	while (count < len && s1[count] != '\0')
	{
		str[count] = s1[count];
		count++;
	}
	count2 = 0;
	while (count < len && s2[count2] != '\0')
	{
		str[count] = s2[count2];
		count++;
		count2++;
	}
	str[count] = '\n';
	str[count + 1] = '\0';
	return (free(s1), str);
}

t_heredock	*free_heredock(t_heredock *heredock)
{
	t_heredock	*tmp;

	while (heredoc)
	{
		tmp = heredock->next;
		free (heredock->key);
		free(heredock);
		heredock = tmp;
	}
	return (NULL);
}

t_heredock	*reading_until_last_key(t_heredock *heredock)
{
	char	*input;
	t_heredock	*temp;

	input = NULL;
	while (heredock->next != NULL)
	{
		if (heredock->key == NULL)
			return (free_heredock((heredock)));
		input = readline("> ");
		if (!input || ft_strcmp(input, heredock->key) == 0) // handleling the EOF already
		{
			if (!input)
				printf("warning: here-document delimited by end-of-file (wanted '%s')!\n", heredock->key);
			input = NULL;
			temp = heredock;
			heredock = heredock->next;
			free(temp->key);
			free(temp);
		}
	}
	return (heredock);
}

void	key_that_metters(t_heredock *last_node)
{
	char	*input;

	input = NULL;

	last_node->fullinput_until_key = ft_strdup("");
	while (1)
	{
		input = readline("> ");
		if (!input || ft_strcmp(input, last_node->key) == 0)
		{
			if (!input)
				printf("warning: here-document delimited by end-of-file (wanted '%s')!\n", last_node->key);
			return ;
		}
		else
			last_node->fullinput_until_key = ft_strjoin_w_new_line(last_node->fullinput_until_key, input);
	}
}

// change it to return an error code (1), if heredoc couldnt finish
int	doing_heredock(t_heredock *heredock)
{
	t_heredock	*last_node;

	last_node = reading_until_last_key(heredock);
	if (last_node == NULL)
		return (heredoc_error());
	key_that_metters(last_node);
	free(last_node->key);
//	ft_putstr_fd(last_node->fullinput_until_key, 1);
	//free_heredock(last_node);
	return (0); // will not return, it will direct it to stdout
}

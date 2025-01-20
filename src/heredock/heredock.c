/*
#include "minishell.h"

int	heredoc_error()
{
	ft_putstr_fd("bash: syntax error near unexpected token `newline'\n", 2);
	return (1);
}

t_heredock	*free_heredock(t_heredock *heredock)
{
	t_heredock	*tmp;

	while (heredock)
	{
		tmp = heredock->next;
		free (heredock->key);
		if (heredock->fullinput_until_key)
			free (heredock->fullinput_until_key);
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
	if (heredock->key == NULL)
		return (free_heredock((heredock)));
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

// need to take off later
/// @brief Function will create and write the inputed heredoc into a temp file
/// @param write
/// @return (file_fd -> success) (NULL -> error)
int	creating_temp_file(char *write)
{
	char	*where_to_write;
	int		file_fd;

	where_to_write = ft_strdup("../tmpFile");
	// need to make it a temp file
	file_fd = open(where_to_write, O_RDWR | O_CREAT, NULL);
	if (file_fd != -1)
		ft_putstr_fd(write, file_fd);
	free (where_to_write);
	return (file_fd);
}

// change it to return an error code (1), if heredoc couldnt finish
int	doing_heredock(t_heredock *heredock)
{
	t_heredock	*last_node;
	int			heredoc_fd;

	last_node = reading_until_last_key(heredock);
	if (last_node == NULL)
		return (heredoc_error());
	key_that_metters(last_node);
	heredoc_fd = creating_temp_file(last_node->fullinput_until_key);
	printf("heredoc done! fd = |%d|\n", heredoc_fd);
	close(heredoc_fd);
	// rewrite the string adding the redirection to the fd file. Ex: (cat << ola) -> (cat < file_fd)
	//printf("%s\n", last_node->fullinput_until_key);
	free_heredock(last_node);
	return (0); // will not return, it will direct it to stdout
}
 */

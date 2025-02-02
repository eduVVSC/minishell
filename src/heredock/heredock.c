#include "minishell.h"

void	doing_key(t_heredock *heredock)
{
	char	*input;

	input = NULL;

	heredock->fullinput_until_key = ft_strdup("");
	while (1)
	{
		input = readline("> ");
		if (!input || ft_strcmp(input, heredock->key) == 0)
		{
			if (!input)
				printf("warning: here-document delimited by end-of-file (wanted '%s')!\n", heredock->key);
			return ;
		}
		else
			heredock->fullinput_until_key = ft_strjoin_w_new_line(heredock->fullinput_until_key, input);
	}
}

/// @brief Function will create and write the inputed heredoc into a temp file
/// @param write
/// @return (file_fd -> success) (NULL -> error)
int	creating_temp_file(char *write)
{
	int		file_fd;

	file_fd = open(TMPFILE, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (file_fd != -1)
		ft_putstr_fd(write, file_fd);
	close(file_fd);
	return (0);
}

// change it to return an error code (1), if heredoc couldnt finish
int	doing_heredock(t_shell *shell, t_heredock *heredock)
{
	int			heredoc_fd;

	
	doing_key(heredock);
	heredoc_fd = creating_temp_file(heredock->fullinput_until_key);
	if (heredoc_fd == -1)
	{
		free_heredock(heredock);
		file_error(shell);
	}
	heredoc_fd = open(TMPFILE, O_RDWR);
	free_heredock(heredock);
	return (heredoc_fd);
}

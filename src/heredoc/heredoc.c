#include "minishell.h"

int	doing_key(t_heredock *heredock)
{
	char	*input;

	input = NULL;
	heredock->fullinput_until_key = ft_strdup("");
	while (1)
	{
		input = readline("> ");
		if (g_sig_sign == SIGINT)
		{
			if (input)
				free (input);
			return (TRUE);
		}
		if (!input || ft_strcmp(input, heredock->key) == 0)
		{
			if (!input)
				printf("warning: here-document delimited by end-of-file (wanted '%s')!\n", heredock->key);
			return (FALSE);
		}
		else
			heredock->fullinput_until_key = ft_strjoin_w_new_line(heredock->fullinput_until_key, input);
	}
	return (FALSE);
}

// change it to return an error code (1), if heredoc couldnt finish
void	doing_heredock(t_shell *shell, t_heredock *heredock, int fd)
{
	int	heredoc_fd;

	if (doing_key(heredock))
	{
		free_heredock(heredock);
		return ;
	}
	if (heredock->state != single_quo)
		heredock->fullinput_until_key = handle_expension(shell->env, heredock->fullinput_until_key);
	if (ft_strlen(heredock->fullinput_until_key) > 1000000)
	{
		free_heredock(heredock);
		pipe_error();
		return ;
	}
	ft_putstr_fd(heredock->fullinput_until_key, fd);
	free_heredock(heredock);
}

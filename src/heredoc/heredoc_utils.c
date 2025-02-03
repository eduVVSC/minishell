
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


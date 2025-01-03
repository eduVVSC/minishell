
#include "minishell.h"

char	*ft_strjoin_w_new_line(char const *s1, char const *s2)
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
	return (str);
}

int	ft_strcmp_sz(const char *s1, const char *s2, size_t n)

{
	size_t	count;

	count = 0;
	if (ft_strlen(s1) != ft_strlen(s2))
		return (-1);
	while (count < n && (s1[count] != '\0' || s2[count] != '\0'))
	{
		if (s1[count] != s2[count])
			return ((unsigned char)(s1[count]) - (unsigned char)(s2[count]));
		count++;
	}
	return (0);
}

t_heredock	*reading_until_last_key(t_heredock *heredock)
{
	char	*input;
	t_heredock	*temp;

	printf("heredock = |%s|\n", heredock->key);
	while (heredock->next != NULL)
	{
		input = readline("> ");
		if (!input || ft_strcmp_sz(input, heredock->key, heredock->key_len) == 0) // handleling the EOF already
		{
			if (!input)
				printf("warning: here-document delimited by end-of-file (wanted '%s')!\n", heredock->key);
			input = NULL;
			temp = heredock;
			heredock = heredock->next;
			free(temp);
		}
	}
	return (heredock);
}

void	key_that_metters(t_heredock *last_node)
{
	char	*input;

	input = NULL;

	while (1)
	{
		input = readline("> ");
		if (!input || ft_strcmp_sz(input, last_node->key, last_node->key_len) == 0)
		{
			if (!input)
				printf("warning: here-document delimited by end-of-file (wanted '%s')!\n", last_node->key);
			return ;
		}
		else
			last_node->fullinput_until_key = ft_strjoin_w_new_line(last_node->fullinput_until_key, input);
	}
}

t_heredock	*doing_heredock(t_heredock *heredock)
{
	t_heredock	*last_node;

	last_node = reading_until_last_key(heredock);
	key_that_metters(last_node);
	return (last_node);
}

/*  int	main(int ac, char **av,char **envp)
{
	t_heredock *heredock;
	t_heredock *node1;
	//t_heredock *node2;

	heredock = malloc(sizeof(t_heredock));
	node1 = malloc(sizeof(t_heredock));
	//node2 = malloc(sizeof(t_heredock));

	heredock->key = "foda-se pa";
	heredock->key_len = 1;
	heredock->next = node1;
	node1->fullinput_until_key = "";
	node1->key = "2";
	node1->key_len = 1;
	node1->next = NULL;

	printf("aqui\n");
	//node2->key = "2";
	//node2->next = NULL;

	heredock = doing_heredock(heredock);
	printf("%s\n", heredock->fullinput_until_key);
	return (0);
} */

// just need to finish this one, and its ready I think?
/* t_heredock	*creating_heredock_list(t_tokens *tokens)
{
	t_heredock	*heredock;

	heredock = malloc(sizeof(t_heredock));

	while(tokens != NULL)
	{

	}
} */

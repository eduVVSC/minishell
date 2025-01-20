/*
#include "minishell.h"

int	check_heredoc_token(char *key)
{
	if (ft_strcmp(key, "<<") == 0)
		return (1);
	else if (ft_strcmp(key, ">>") == 0)
		return (1);
	else if (ft_strcmp(key, "|") == 0)
		return (1);
	return (0);
}

int	check_heredoc_command(t_tree_node *node)
{
	int	i;

	i = 0;
	while (node->content[++i])
	{
		if (ft_strcmp(node->content[i], "<<") == 0)
		{
			if (!node->content[++i])
				return (0);
			else if (check_heredoc_token(node->content[i]) == 1)
				return (1);
		}
	}
	return (0);
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
 */

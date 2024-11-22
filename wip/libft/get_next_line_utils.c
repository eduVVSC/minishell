/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:20:16 by dioferre          #+#    #+#             */
/*   Updated: 2024/10/05 18:54:42 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr_gnl(char *s, int c)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == *s)
		return ((char *)s);
	return (NULL);
}

char	*ft_strdup_gnl(const char *s)

{
	char	*str;
	size_t	count;
	size_t	len;

	len = ft_strlen_gnl(s);
	count = 0;
	str = malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	while (s[count] != '\0')
	{
		str[count] = s[count];
		count++;
	}
	str[count] = '\0';
	return (str);
}

char	*ft_substr_gnl(char *s, unsigned int start, size_t len)

{
	char	*substr;
	size_t	count;

	count = 0;
	if (!s)
		return (NULL);
	if (start > ft_strlen_gnl(s))
		return (ft_strdup(""));
	if (len > ft_strlen_gnl(s + start))
		len = ft_strlen_gnl(s + start);
	substr = malloc((len + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	while (count < len)
	{
		substr[count] = s[start + count];
		count++;
	}
	substr[count] = '\0';
	return (substr);
}

void	*ft_calloc_gnl(size_t nmemb, size_t size)

{
	unsigned char	*tmp;
	size_t			i;

	i = 0;
	tmp = malloc(nmemb * size);
	if (!tmp)
		return (NULL);
	while (i < (nmemb * size))
	{
		tmp[i] = 0;
		i++;
	}
	return (tmp);
}

char	*ft_strjoin_gnl(char *s1, char *s2)

{
	char	*str;
	int		i;
	int		j;
	int		len;

	i = 0;
	len = (ft_strlen_gnl(s1) + ft_strlen_gnl(s2));
	str = ft_calloc_gnl((len + 1), sizeof(char));
	if (!str)
		return (NULL);
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	free (s1);
	return (str);
}

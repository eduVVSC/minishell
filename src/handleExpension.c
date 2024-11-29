#include "../include/minishell.h"

size_t	ft_strlen(const char *s)
{
	size_t	count;

	count = 0;
	while (s[count])
		count++;
	return (count);
}

/* // the flag will tell if our function is counting the left or the right side of the env_variable

// 1 -> right_side    0 -> left_side
int	count_quoutes(char *str, int start, int flag)
{
	int	many_quotes;

	many_quotes = 0;
	while(str[start] != 27 && str[start] != 22)
	{
		if(str[start] == 27) // single quote
			many_quotes++;
		else if(str[start] == 22) // double quotes
			many_quotes += 2;

		if (flag == 1)
			start++;
		else if (flag == 0)
			start--;
	}
} */

// function will check if the variable needs to expand
// if so, return the name of the expand, else, return an empty string
int	check_expxand(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if(str[i] == '$')
			return (i);
		i++;
	}
	return (-1);
}

// receive var_len + 1, because you are not counting the '$' in it
char	*re_wrinting_string(char *str, char *expand_value, int where_to_change, int var_len)
{
	char	*new_str;
	int		k;
	int		i;
	int		j;

	i = -1;
	j = -1;
	k = 0;
	new_str = malloc(sizeof(char) * (ft_strlen(str) - var_len + ft_strlen(expand_value) + 1));
	while (++i < where_to_change)
		new_str[i] = str[i];
	while (expand_value[++j] != 0)
		new_str[i + j] = expand_value[j];
	j = i + j;
	i++;
	while (str[i] != ' ' && str[ i] != '\0')
		i++;
	while (str[i + k] != '\0')
	{
		new_str[j + k] = str[i + k];
		k++;
	}
	new_str[j + k] = '\0';
	return (new_str);
}

char	*var_name(char *str, int start)
{
	char	*var_name;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	while(str[start + i] != ' ' && str[start + i] != '\0')
		i++;
	var_name = malloc(sizeof(char) * (i + 1));
	i = 0;
	while(str[start + i] != ' ' && str[start + i] != '\0')
	{
		var_name[i] = str[start + i];
		i++;
	}
	var_name[i] = 0;
	return (var_name);
}

char	*handle_expension(char *str)
{
	int		flag;
	char	*var;
	char	*var_value;

	flag = 0;
	while (flag != -1)
	{
		flag = check_expand(str);
		if(flag != -1)
		{
			var = var_name(str, (flag + 1));
			var_value =  getenv(var);
			printf("%s = %s\n",var, var_value);
			if (var_value == NULL)
				var_value = "";
			str = re_wrinting_string(str, var_value, flag, (ft_strlen(var) + 1));
		}
	}
	free(var);
	return (str);
}

/*
int main(int ac, char **av)
{
	char *str = "hello $USER go fuck yourself";

	printf("%s\n", handle_expension(str));
	//printf("%d\n", count_quoutes(av[1], 2, 0));
	//printf("%d\n", count_quoutes(av[1], 2 + ft_strlen(var_name(av[1], 2)), 1));

	return (0);
} */

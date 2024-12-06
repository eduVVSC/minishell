#include "minishell.h"

// Receive the string and Returns the index of the $
// Function will search for the $
int	check_expand(char *str)
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

// Receive the string, the value of the var and where it is Returns the new string with the value in it
// Function will rewrite the string to the value of the variable inputed, free the received string
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
	while((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z'))
		i++;
	while (str[i + k] != '\0')
	{
		new_str[j + k] = str[i + k];
		k++;
	}
	new_str[j + k] = '\0';
	free(str);
	return (new_str);
}

// Receive the string and where the variable starts and Returns the variable name
// Function will search for the $ and get the inputed variable name
char	*var_name(char *str, int start)
{
	char	*var_name;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	while((str[start + i] >= 'a' && str[start + i] <= 'z') || (str[start + i] >= 'A' && str[start + i] <= 'Z'))
		i++;
	var_name = malloc(sizeof(char) * (i + 1));
	i = 0;
	while((str[start + i] >= 'a' && str[start + i] <= 'z') || (str[start + i] >= 'A' && str[start + i] <= 'Z'))
	{
		var_name[i] = str[start + i];
		i++;
	}
	var_name[i] = 0;
	return (var_name);
}

// Receive the string and returns the string with the expansion
// Function will search for the expansion(if it has something to be expanded) and rewrite the string with the var value
char	*handle_expension(char *str)
{
	int		flag;
	char	*var;
	char	*var_value;

	flag = 0;
	var = NULL;
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

// Receive the string and returns the new_string
// Function take the quotes of the string and free the old string
char	*takeoff_quotes(char *str)
{
	char	*new_str;
	int		strlen;
	int		i;

	i = 0;
	strlen = ft_strlen(str);
	new_str = malloc((strlen - 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	while (++i < (strlen- 1))
		new_str[i - 1] = str[i];
	new_str[i -1] = '\0';
	free(str);
	return (new_str);
}

// Receive the token
// function check if it needs to be expanded and expand the token
void	*expand_token(t_tokens *token)
{
	if (!token->token)
		exit (1);
	if (token->state == double_quo || token->state == single_quo)
		token->token = takeoff_quotes(token->token);
	if (token->state == double_quo || token->state == general || token->state == expanded)
		token->token = handle_expension(token->token);
}
